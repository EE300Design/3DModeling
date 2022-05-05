#include <SoftwareSerial.h> //header file of software serial port
//The next line is commented as we are using mega
//SoftwareSerial Serial1(7,8); //define software serial port name as Serial1 and define pin7 as RX and pin8 as TX

/* For Arduinoboards with multiple serial ports like DUEboard, interpret above two pieces of code and directly use Serial1 serial port*/
int dist; //actual distance measurements of LiDAR 
int strength; //signal strength of LiDAR
float x_cor;
float y_cor;

int check; //save check value
int i;
int uart[9]; //save data measured by LiDAR
const int HEADER=0x59; //frame header of data package 

// defines pins numbers
const int stepPin1 = 4; 
const int dirPin1 = 3; 
const int stepPin2 = 5; 
const int dirPin2 = 6; 

const int heightIncrement = 20; // Height increment amount after one disk rotation


void setup() {
  Serial.begin(9600); //set bit rate of serial port connecting Arduino with computer
  Serial1.begin(115200); //set bit rate of serial port connecting LiDAR with Arduino 
    // For Stepper Motors, sets the four pins as Outputs
  pinMode(stepPin1,OUTPUT); // Disk rotation motor
  pinMode(dirPin1,OUTPUT);
  pinMode(stepPin2,OUTPUT); // Screw rotation motor
  pinMode(dirPin2,OUTPUT);
  pinMode(7,INPUT);
  pinMode(8, OUTPUT);
}


float heightData = 0;
int h = 0;
const int Length = 50; //sensor to the center of disk distance in cm


void start_scan()//
{
  delay(100);
  bool exit_scan=false;
    //Set scanning max height limit 360 is found by 7200steps/20
  while(!exit_scan) {
    
    float theta = 0; // Angle of the disk rotation
    digitalWrite(dirPin1,LOW); // Enables the motor to move in a particular direction
    // Makes 200 pulses for making one full cycle rotation
    for(int x = 0; x < 200;) {
     int interrupt = digitalRead(7);
     if(interrupt == HIGH){
      
       //Serial.print('H');
       //Serial.write(interrupt);
       digitalWrite(8,interrupt);
       exit_scan = true;
       break;
      }
     
     if (Serial1.available()) { //check if serial port has data input
        if(Serial1.read() == HEADER) { //assess data package frame header 0x59 
          uart[0]=HEADER;
            if (Serial1.read() == HEADER) { //assess data package frame header 0x59
              uart[1] = HEADER;
              for (i = 2; i < 9; i++) { //save data in array
                uart[i] = Serial1.read(); 
                }
              check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7]; 
              if (uart[8] == (check & 0xff)) { //verify the received data as per protocol
                dist = uart[2] + uart[3] * 256; //calculate distance value [cm]
                strength = uart[4] + uart[5] * 256; //calculate signal strength value 
          
                Serial1.flush();
                digitalWrite(stepPin1,HIGH); 
                delayMicroseconds(1500); 
                digitalWrite(stepPin1,LOW); 
                delayMicroseconds(1500);
                theta += 1.8;

                x++;
                // check if one full rotation completed
                if (x==200){
                  digitalWrite(dirPin2,LOW); // Enables the motor to move in clockwise direction
                                             // Makes 200 pulses for making one full cycle rotation
 
                  for(int x = 0; x < heightIncrement; x++) {
                      digitalWrite(stepPin2,HIGH); 
                      delayMicroseconds(500); 
                      digitalWrite(stepPin2,LOW); 
                      delayMicroseconds(500); 
                    }
    
                  h += heightIncrement; // counting height rotation steps
                  heightData = heightData + h/24.0; // calculate the hieght
                  }

                // Perform coordinate conversion  
                Serial.print(dist);
                Serial.print(' ');
                x_cor = (Length-dist)*cos((theta/180) * 3.14159);
                y_cor = (Length-dist)*sin((theta/180) * 3.14159);
                Serial.print(x_cor); // output disk rotation angle
                Serial.print(' ');
                Serial.print(y_cor);
                Serial.print(' ');
                Serial.println(heightData);
               
                
          } 
         }
       }
    }
    
      
  }
  
    delay(1000); // One second delay
  

 }
 Serial.println("scan exited");
 digitalWrite(8,LOW);
 
}

void stop_scan(){

  delay(2000);
  }

//This version can scan continuously without a command sent from MATLAB
void loop() {

    if (Serial.available() <= 0) {
    // read the oldest byte in the serial buffer:
      start_scan();
//    int incomingByte = Serial.read();
//    // if it's a capital H (ASCII 72), begin scanning
//    if (incomingByte == 'H') {
//      start_scan();
//    }
//    // if it's an L (ASCII 76) stops scanning
//    if (incomingByte == 'L') {
//      stop_scan();
//    }
  }
    
 }

 

  
  

  
  








   
