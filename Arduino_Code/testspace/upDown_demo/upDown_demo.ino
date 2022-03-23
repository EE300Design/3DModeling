void setup() {
  // put your setup code here, to run once:
 pinMode(3,OUTPUT);
 pinMode(4,OUTPUT);
 pinMode(5,OUTPUT);
 pinMode(6,OUTPUT);

 digitalWrite(3,HIGH);
}
  const int stepPin1 = 4;
  const int dirPin1 = 3;
  const int stepPin2 = 5;
  const int dirPin2 = 6;
  int de = 2500;
  
void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<200;i++){
    digitalWrite(stepPin1,HIGH);
    delayMicroseconds(de);
    digitalWrite(stepPin1,LOW);
    delayMicroseconds(de);
  }
//  delay(1000);
//  
//  digitalWrite(dirPin1,LOW);
//  for(int i=0;i<200;i++){
//    digitalWrite(stepPin1,HIGH);
//    delayMicroseconds(500);
//    digitalWrite(stepPin1,LOW);
//    delayMicroseconds(500);
//  }
//  delay(1000);  
//  
//  digitalWrite(dirPin2,HIGH);
//  for(int i=0;i<200;i++){
//    digitalWrite(stepPin2,HIGH);
//    delayMicroseconds(500);
//    digitalWrite(stepPin2,LOW);
//    delayMicroseconds(500);
//  }
//  delay(1000);
//  
//  digitalWrite(dirPin2,LOW);
//  for(int i=0;i<200;i++){
//    digitalWrite(stepPin2,HIGH);
//    delayMicroseconds(500);
//    digitalWrite(stepPin2,LOW);
//    delayMicroseconds(500);
//  }
//  delay(1000);
}
