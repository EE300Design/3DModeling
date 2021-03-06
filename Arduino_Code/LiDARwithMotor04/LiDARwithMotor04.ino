#include <SoftwareSerial.h> //header file of software serial port
SoftwareSerial Serial1(7,8); //define software serial port name as Serial1 and define pin2 as RX and pin3 as TX

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
const int LimSwitchUp = 1;
const int LimSwitchDw = 2;
const int stepPin1 = 3; //horizontal rotation 
const int dirPin1 = 4;  // rotation
const int stepPin2 = 5; // rotation for up/down
const int dirPin2 = 6; 

const int heightIncrement = 20; // Height increment amount after one disk rotation
bool interrupt = false; // interruption flag


void setup() {
  Serial.begin(9600); //set bit rate of serial port connecting Arduino with computer
  Serial1.begin(115200); //set bit rate of serial port connecting LiDAR with Arduino 
    // For Stepper Motors, sets the four pins as Outputs
  pinMode(stepPin1,OUTPUT); // Disk rotation motor
  pinMode(dirPin1,OUTPUT);
  pinMode(stepPin2,OUTPUT); // Screw rotation motor
  pinMode(dirPin2,OUTPUT);
  pinMode(LimSwitchUp, INPUT);
  pinMode(LimSwitchDw, INPUT);
  pinMode(9,INPUT);
}


float heightData = 0;
int h = 0;
const int Length = 40; //sensor to the center of disk distance




void stop_scan(){

  interrupt = true;
  digitalWrite(dirPin1,LOW); // Set the motor pins to a fixed value to stop them
  digitalWrite(stepPin1,HIGH); 
  digitalWrite(dirPin2,LOW); //
  digitalWrite(stepPin2,HIGH); 
  
  }

void reset_scan(){
  stop_scan();
  while (!digitalRead(LimSwitchDw)){
  Rotation(dirPin2,stepPin2, 0, 100);
  }
  
  }

void Rotation (int dirPin, int stepPin, int dir, int freq){
  if (dir == 1){
    digitalWrite(dirPin,LOW); // rotate the screw upwards
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(freq); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(freq);
  }

  else if (dir == 0){ // Rotate the screw downwards
    digitalWrite(dirPin,HIGH); //Changes the rotations direction
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(freq);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(freq);
 }
    
    }
  
  

  // while (limit switch ...)
  //{Rotation (0)}



void start_scan()//
{
  delay(1000);
    //Set scanning max height limit 360 is found by 7200steps/20
  for(int n = 0; n < 360; n++) {

    float theta = 0; // Angle of the disk rotation
    
    // Makes 200 pulses for making one full cycle rotation
    for(int x = 0; x < 200;) {

//     Serial.begin(9600);
//     if (Serial.available() > 0) {
//    // read the oldest byte in the serial buffer:
//    int interruptByte = Serial.read();
//    // if it's a capital I set the interrupt to true
//    if (interruptByte == 'I') {
//      stop_scan();
//    }
      int interruptButton = digitalRead(9);
    if(interruptButton == HIGH){
      
       stop_scan();
//       Serial.print('H');
//       //Serial.write(secondSensor);
//       digitalWrite(4,interruptButton);
      }
//     else {
//      Serial.print('L');
//      digitalWrite(4,interruptButton);
//      }
//      delay(1000);
//
//      Serial.end();
//
//      delay(5000);
//      Serial.begin(9600);
//      Serial.println('B');
     
     if (Serial1.available() && !interrupt) { //check if serial port has data input
        if(Serial1.read() == HEADER) { //assess data package frame header 0x59 
          uart[0]=HEADER;
            if (Serial1.read() == HEADER) { //assess data package frame header 0x59
              uart[1] = HEADER;
              
              for (i = 2; i < 9; i++) { //save data in array
                uart[i] = Serial1.read(); 
                }
              check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7]; 
              if (uart[8] == (check & 0xff)) { //verify the received data as per protocol
                dist = uart[2] + uart[3] * 256; //calculate distance value 
                strength = uart[4] + uart[5] * 256; //calculate signal strength value 
                //Serial1.flush(); // flush the buffer.
                
//                digitalWrite(dirPin1,LOW); // 
//                digitalWrite(stepPin1,HIGH); 
//                delayMicroseconds(10); 
//                digitalWrite(stepPin1,LOW); 
//                delayMicroseconds(10);
                Rotation (dirPin1, stepPin1, 1, 100); // dir = 1 , freq = 100 in ms
                theta += 1.8;

                x++;
                // check if one full rotation completed
                if (x==200){
                   // Enables the motor to move in clockwise direction
                   // Makes 200 pulses for making one full cycle rotation
 
                  for(int ht = 0; ht < heightIncrement; ht++) {
                      digitalWrite(dirPin2,LOW); // motor moving up
                      digitalWrite(stepPin2,HIGH); 
                      delayMicroseconds(500); 
                      digitalWrite(stepPin2,LOW); 
                      delayMicroseconds(500); 
                    }
    
                  h += heightIncrement; // counting height rotation steps
                  heightData = heightData + h/24.0; // calculate the hieght
                  }

                // Perform coordinate conversion  
                x_cor = (Length-dist)*cos((theta/180) * 3.14159);
                y_cor = (Length-dist)*sin((theta/180) * 3.14159);
                Serial.print(x_cor); // output disk rotation angle
                Serial.print(' ');
                Serial.print(y_cor);
                Serial.print(' ');
                Serial.println(heightData);
                //Serial.flush();
               
                
          } 
         }
       }
    delay(1000);
    Serial.end();
    }

    ////////////Scann Interrupted
    else {
      
      Serial.println('interrupted');
      }
    
      
  }
  
    delay(1000); // One second delay
  

 }
}




void loop() {
    interrupt = false;
    if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    int incomingByte = Serial.read();
    // if it's a capital H (ASCII 72), begin scanning
    if (incomingByte == 'H') {
      start_scan();
    }
    // if it's an L (ASCII 76) stops scanning
    else if (incomingByte == 'L') {
      stop_scan();
    }
    else if (incomingByte == 'R'){
      reset_scan();
      
      }
    
  }
    
 }

 

  
  

  
  








   
