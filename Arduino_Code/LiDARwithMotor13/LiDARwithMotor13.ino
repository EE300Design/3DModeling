//#include <SoftwareSerial.h> //header file of software serial port
//The next line is commented as we are using mega
//SoftwareSerial Serial1(7,8); //define software serial port name as Serial1 and define pin7 as RX and pin8 as TX

//This version deals with limiting switches

/* For Arduino boards with multiple serial ports like DUEboard, interpret the above two pieces of code and directly use Serial1 serial port*/
int dist; //actual distance measurements of LiDAR 
int strength; //signal strength of LiDAR
float x_cor;
float y_cor;

//////////////////////////////
int check; //save check value
int i;
int uart[9]; //save data measured by LiDAR
const int HEADER=0x59; //frame header of data package 

// defines pins numbers
// Disk rotation motor
const  int stepPin1 = 8; 
const  int dirPin1 = 9; 
// Screw rotation motor
const int stepPin2 = 3; 
const int dirPin2 = 2; 
// Set up for limiting switches
const int LimSwitchUp = 7;
const int LimSwitchDw = 6;

const int heightIncrement = 80; // Height increment amount after one disk rotation


void setup() {
  Serial.begin(9600); //set bit rate of serial port connecting Arduino with computer
  Serial1.begin(115200); //set bit rate of serial port connecting LiDAR with Arduino 
    // For Stepper Motors, sets the four pins as Outputs
  pinMode(stepPin1,OUTPUT); // Disk rotation motor
  pinMode(dirPin1,OUTPUT);
  pinMode(stepPin2,OUTPUT); // Screw rotation motor
  pinMode(dirPin2,OUTPUT);
  //pinMode(1,INPUT);// interrupt button
  pinMode(LimSwitchUp, INPUT);
  pinMode(LimSwitchDw, INPUT);
}


float heightData = 0;
int h = 0;
const float Length = 47.0; //sensor to the center of disk distance in cm


/////////////// https://forum.arduino.cc/t/solved-flush-serial-input-buffer/525657/22 Juraj
void serial_flush() {
  for (int i = 0 ; i < 900; i++){
  Serial1.read();
  }
}


void stop_scan(){
  digitalWrite(dirPin1,LOW); // Set the motor pins to a fixed value to stop them
  digitalWrite(stepPin1,HIGH); 
  digitalWrite(dirPin2,LOW); //
  digitalWrite(stepPin2,HIGH); 
  //digitalWrite(7,LOW);
  // Later, need to record the index where it stopped so that it can properly resume.
  
  }

// Ref



void start_scan()//
{
  delay(1000);
  bool exit_scan=false;
    //Set scanning max height limit 360 is found by 7200steps/20
  while(!exit_scan) {
    
    float theta = 0; // Angle of the disk rotation
    digitalWrite(dirPin1,LOW); // Enables the motor to move in a particular direction
    
    
    int overshoot = 0; // Overshoot counter
    // Makes 200 pulses for making one full cycle rotation
    for(int x = 0; x < 200;) {
     int UpLim = digitalRead(LimSwitchUp);
     int DwLim = digitalRead(LimSwitchDw);
     //int interrupt = LOW; // need to fix this, changing to protenta interrupt
     //interrupt = digitalRead(1); // need to fix this
     
//     if(interrupt == HIGH){ // protenta is HIGH when open
//      
//       stop_scan();
//       digitalWrite(11,interrupt);
//       Serial.println("Interrupted");
//       exit_scan = true;
//       break;
//      }

      //Check if the upper limiting switch is pressed
      
      if(UpLim == HIGH){
        Serial.println("Move Down");
        digitalWrite(dirPin2,HIGH);
        
        //If pressed, rotates the carriage downward till initial position
        while(DwLim == LOW){
        DwLim = digitalRead(LimSwitchDw);
        digitalWrite(stepPin2,HIGH); 
        delayMicroseconds(400); 
        digitalWrite(stepPin2,LOW); 
        delayMicroseconds(400);
        }
        exit_scan = true;
        break;
        }

     if (Serial.available() > 0) {
       int incomingByte = Serial.read();
    // if it's a capital R (ASCII 82 ), stop scanning
    if (incomingByte == 'R') {
      Serial.println("reset");
      stop_scan();
      digitalWrite(dirPin2,HIGH);
                  
      //If scan reset triggered, rotates the carriage downward till initial position
      while(DwLim == LOW){
      DwLim = digitalRead(LimSwitchDw);
      digitalWrite(stepPin2,HIGH); 
      delayMicroseconds(700); 
      digitalWrite(stepPin2,LOW); 
      delayMicroseconds(700);
      }
      exit_scan = true;
      break;
    }
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
                dist = uart[2] + uart[3] * 256; //calculate distance value [mm]
                float cmdist = dist/10.0;  // convert to cm
                //strength = uart[4] + uart[5] * 256; //calculate signal strength value 

                //Serial1.flush();  // This flush makes serial unstable.
                ////////////////////////Check overshooting, if ten continuous points overshoot it means the scanning is done.
                if (cmdist > 47|| (h == 10)){
                  overshoot += 1;
                  if (overshoot == 10|| (h == 10)){
                          Serial.println("d");

                          stop_scan();
                          digitalWrite(dirPin2,HIGH);
                                      
                          //If scan reset triggered, rotates the carriage downward till initial position
                          while(DwLim == LOW){
                          DwLim = digitalRead(LimSwitchDw);
                          digitalWrite(stepPin2,HIGH); 
                          delayMicroseconds(700); 
                          digitalWrite(stepPin2,LOW); 
                          delayMicroseconds(700);
                          }
                          exit_scan = true;
                          break;
                    }
                  }
                
                delay(100);
                digitalWrite(stepPin1,HIGH); 
                delayMicroseconds(100); 
                digitalWrite(stepPin1,LOW); 
                delayMicroseconds(100);
                
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
    
                  h += 1; // counting height rotation steps
                  heightData = (h*heightIncrement/10)/26.7; // calculate the hieght in cm
                  }

                // Perform coordinate conversion  
                Serial.println(cmdist);
//                Serial.print(' ');
//                //Serial.print(h);
//                x_cor = (Length-cmdist)*cos((theta/180) * 3.14159);
//                y_cor = (Length-cmdist)*sin((theta/180) * 3.14159);
//                Serial.print(x_cor); // output disk rotation angle
//                Serial.print(' ');
//                Serial.print(y_cor);
//                Serial.print(' ');
//                Serial.println(heightData);
               
                
          } 
         }
       }
    }
    
      
  }
  
 }
 
}




//This version can take string sent from MATLAB and be reset by limiting switches
// Issues:
/*
 * The serial communication was not stable, scanning stops itself from time to time
 * Need to format the data, sending the distances only.
 * Need to avoid any racing conditions.
 */

void loop() {

    if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
      
    int incomingByte = Serial.read();
    // if it's a capital H (ASCII 72), begin scanning
    if (incomingByte == 'H') {
      Serial.println("start");
      start_scan();
      serial_flush();
    }
    // if it's an L (ASCII 76) stops scanning
    if (incomingByte == 'L') {
      stop_scan();
    }
  }
    
 }

  
  

  



   
