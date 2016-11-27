#include <TimedAction.h>

#include "RobotDrive.h"
#include "RobotUltrasonic.h"
#include "RobotWifi.h"

int programModePin = 31;
int chargeModePin = 33;
int ledPin = 13;

RobotWifi wifi;
RobotDrive drive = RobotDrive();
RobotUltrasonic ultrasonic = RobotUltrasonic();

void checkMode(){

  boolean chargeMode = (digitalRead(chargeModePin) == HIGH);
  boolean programMode = (digitalRead(programModePin) == LOW);

  if(!wifi.checkWifi()){
    stopRobot();
    wifi.waitForWifi();
  }
  if(!drive.checkSensors()){
    stopRobot();
    drive.waitForIMU();
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
      if(!drive.checkSensors()){
        drive.waitForIMU();
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
      if(!drive.checkSensors()){
        drive.waitForIMU();
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
      if(!drive.checkSensors()){
        drive.waitForIMU();
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

void setup() {

  pinMode(programModePin, INPUT_PULLUP);
  pinMode(chargeModePin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  wifi.setup();
  drive.setup(checkThread);
  ultrasonic.setup(checkThread);
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
  autonomous();
}

void autonomous(){
  drive.driveSpeed(255);
}

