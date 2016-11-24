#include "Arduino.h"
#include <NewPing.h>
#include <Servo.h>
#include "RobotUltrasonic.h"

int triggerPin = 22;
int echoPin = 23;

NewPing sonar(triggerPin, echoPin, 150);
Servo servo;

RobotUltrasonic::RobotUltrasonic(TimedAction ct){
  checkThread = ct;
}

void RobotUltrasonic::setup(){

  servo.attach(9);
  
}

void RobotUltrasonic::stop(){
  servo.detach();
}

void RobotUltrasonic::setViewAngle(int angle){

  servo.write(angle);
  delay(15);
  
}

boolean RobotUltrasonic::ultrasonicInRange(int maxDistance){

  int detected = sonar.ping_cm();

  if(detected <= maxDistance && detected != 0){

    return true;
    
  }

  return false;
  
}

boolean RobotUltrasonic::ultrasonicInRange(int minDistance, int maxDistance){

  int detected = sonar.ping_cm();

  if(detected >= minDistance && detected <= maxDistance && detected != 0){

    return true;
    
  }

  return false;
  
}
