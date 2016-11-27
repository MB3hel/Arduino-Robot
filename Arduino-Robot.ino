#include <TimedAction.h>

#include "RobotDrive.h"
#include "RobotUltrasonic.h"
#include "RobotWifi.h"

int programModePin = 31;
int chargeModePin = 33;
int ledPin = 13;

RobotWifi wifi;

void checkMode(){

  boolean chargeMode = (digitalRead(chargeModePin) == HIGH);
  boolean programMode = (digitalRead(programModePin) == LOW);

  if(!wifi.checkWifi()){
    stopRobot();
    wifi.waitForWifi();
  }
  
  while(programMode || chargeMode){
    while(programMode && chargeMode){ //4 times
  
      stopRobot();
      
      digitalWrite(ledPin, HIGH);
      delay(250);
      digitalWrite(ledPin, LOW);
      delay(250);
      digitalWrite(ledPin, HIGH);
      delay(250);
      digitalWrite(ledPin, LOW);
      delay(250);
      digitalWrite(ledPin, HIGH);
      delay(250);
      digitalWrite(ledPin, LOW);
      delay(250);
      digitalWrite(ledPin, HIGH);
      delay(250);
      digitalWrite(ledPin, LOW);
      delay(1000);

      if(!wifi.checkWifi()){
        wifi.waitForWifi();
      }
       
      chargeMode = (digitalRead(chargeModePin) == HIGH);
      programMode = (digitalRead(programModePin) == LOW);
      
    }
  
    while(programMode && !chargeMode){ //3 times
      
      stopRobot();
      
      digitalWrite(ledPin, HIGH);
      delay(250);
      digitalWrite(ledPin, LOW);
      delay(250);
      digitalWrite(ledPin, HIGH);
      delay(250);
      digitalWrite(ledPin, LOW);
      delay(250);
      digitalWrite(ledPin, HIGH);
      delay(250);
      digitalWrite(ledPin, LOW);
      delay(1000);

      if(!wifi.checkWifi()){
        wifi.waitForWifi();
      }
  
      chargeMode = (digitalRead(chargeModePin) == HIGH);
      programMode = (digitalRead(programModePin) == LOW);
      
    }
  
    while(chargeMode && !programMode){ //2 times
  
      stopRobot();
      
      digitalWrite(ledPin, HIGH);
      delay(250);
      digitalWrite(ledPin, LOW);
      delay(250);
      digitalWrite(ledPin, HIGH);
      delay(250);
      digitalWrite(ledPin, LOW);
      delay(1000);

      if(!wifi.checkWifi()){
        wifi.waitForWifi();
      }
      
      chargeMode = (digitalRead(chargeModePin) == HIGH);
      programMode = (digitalRead(programModePin) == LOW);
      
    }
  }
  startRobot();
}

void checkActions(){
  checkMode();
}

TimedAction checkThread = TimedAction(500, checkActions);

RobotDrive drive = RobotDrive(checkThread);
RobotUltrasonic ultrasonic = RobotUltrasonic(checkThread);


void setup() {

  pinMode(programModePin, INPUT_PULLUP);
  pinMode(chargeModePin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  wifi.setup();
  drive.setup();
  ultrasonic.setup();
  checkMode();
  autonomous();
}

void loop() {
  checkThread.check();
  String message = wifi.getMessage();
}

void delayRobot(long time){
  long startTime = millis();
  while(millis() - startTime <= time){
    checkThread.check();
  }
}

void stopRobot(){
  drive.stopDrive();
  ultrasonic.stop();
}

void startRobot(){
  drive.setup();
  ultrasonic.setup();
  autonomous();
}

void autonomous(){
  drive.driveSpeed(255);
}

