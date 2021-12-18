#include <Servo.h>
Servo servo;
int allowArange = 128;
int angle = 0;
int changeWalkmanTimeBtn = 8;
boolean walkmanTime = true;
void setup() {
  servo.attach(9);
  pinMode(changeWalkmanTimeBtn,INPUT);
  pinMode(7,OUTPUT);
  Serial.begin(9600);
  servo.write(angle);
}

void loop() {
  int changeTimeWalkman = digitalRead(changeWalkmanTimeBtn);
  if(changeTimeWalkman == HIGH){
    if(!walkmanTime){
        walkmanTime = true;
      }else{
        walkmanTime = false;
      }
  }
  if(walkmanTime){digitalWrite(7,HIGH);}
  else if(!walkmanTime){digitalWrite(7,LOW);}
  int p = analogRead(A1);
  Serial.println(p);
  if(walkmanTime){ // If walkman time
    if(p >= 40){ // Car is in area
      if(servo.read()<=10){
        enable();
        delay(5000);
      }
    }else{disable();}
  }else if(!walkmanTime){
      if(servo.read()<=allowArange){ // if car defence is on, disable to car defence
        disable();
      }
  }
  delay(20);
}
void servoWrite(int ag,int delayNum){
  servo.write(angle);
  delay(delayNum);
  }
void enable(){
  for(angle = servo.read();angle<=allowArange;angle++){
    servoWrite(angle,15);
  }
}
void disable(){
  for(angle=servo.read();angle>0;angle--){
    servoWrite(angle,15);
  }
}
