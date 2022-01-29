/*     Simple Stepper Motor Control Exaple Code
 */

// defines pins numbers
const int stepPin1 = 3; 
const int dirPin1 = 4; 
const int stepPin2 = 5;
const int dirPin2 = 6;

void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin1,OUTPUT); 
  pinMode(dirPin1,OUTPUT);
  pinMode(stepPin2,OUTPUT); 
  pinMode(dirPin2,OUTPUT);
  
}

void iterate_steps1(int count, int dir){
  digitalWrite(dirPin1,dir);

  for(int i = 0;i<count;i++){
    digitalWrite(stepPin1,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin1,LOW);
    delayMicroseconds(500); 
  }
}
void iterate_steps2(int count, int dir){
  digitalWrite(dirPin2,dir);

  for(int i = 0;i<count;i++){
    digitalWrite(stepPin2,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin2,LOW);
    delayMicroseconds(500); 
  }
}

void loop() {
  int m = 10;
  int n = 27;
  int theta_step_size = floor(200/n);
  int theta_correction = 200-(n*theta_step_size);

  for(int i=0;i<n;i++){
    iterate_steps1(theta_step_size,LOW);
    delay(100);
  }
  iterate_steps1(theta_correction,LOW);
  iterate_steps2(200,LOW);
  delay(1000);
  
}
