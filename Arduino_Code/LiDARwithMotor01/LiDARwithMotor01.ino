#include <SoftwareSerial.h> //header file of software serial port
SoftwareSerial Serial1(7,8); //define software serial port name as Serial1 and define pin2 as RX and pin3 as TX

/* For Arduinoboards with multiple serial ports like DUEboard, interpret above two pieces of code and directly use Serial1 serial port*/
int dist; //actual distance measurements of LiDAR 
int strength; //signal strength of LiDAR

int check; //save check value
int i;
int uart[9]; //save data measured by LiDAR
const int HEADER=0x59; //frame header of data package 

// defines pins numbers
const int stepPin1 = 3; 
const int dirPin1 = 4; 
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
}


float heightData = 0;
int h = 0;


void loop() {

    //Set scanning max height limit 360 is found by 7200steps/20
  for(int n = 0; n < 360; n++) {

    float theta = 0; // Angle of the disk rotation
    digitalWrite(dirPin1,LOW); // Enables the motor to move in a particular direction
    // Makes 200 pulses for making one full cycle rotation
    for(int x = 0; x < 200; x++) {
      digitalWrite(stepPin1,HIGH); 
      delayMicroseconds(500); 
      digitalWrite(stepPin1,LOW); 
     delayMicroseconds(500);
     theta += 1.8;
     Serial.print("angle = ");
     Serial.print(theta); // output disk rotation angle

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
                dist = uart[2] + uart[3] * 256; //calculate distance value 
                strength = uart[4] + uart[5] * 256; //calculate signal strength value 
          
                Serial.print("dist = ");
                Serial.print(dist); //output measure distance value of LiDAR 
                Serial.print('\t');
                Serial.print("strength = ");
                Serial.println(strength); //output signal strength value
        
          } 
         }
       }
    }
    Serial.print("height = ");
    Serial.println(heightData);
      
  }
  
    delay(100); // One second delay
  

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

  
  

  
  //Wait to introduce lowering down the LiDAR platform
  delay(5000);
  digitalWrite(dirPin2,HIGH);
  for(int x = 0; x < 600; x++) {
    digitalWrite(stepPin2,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin2,LOW); 
    delayMicroseconds(500); 
  }

}







   
