#include <TimedAction.h>

#include "RobotDrive.h"
#include "RobotUltrasonic.h"
#include "RobotWifi.h"

int programModePin = 31;
int chargeModePin = 33;
int ledPin = 13;

RobotWifi wifi;
RobotDrive drive;
RobotUltrasonic ultrasonic;

void checkMode(){

  boolean chargeMode = (digitalRead(chargeModePin) == HIGH);
  boolean programMode = (digitalRead(programModePin) == LOW);
  boolean imuError = !drive.checkSensors();
  boolean wifiError = !wifi.checkWifi();
  
  while(programMode || chargeMode || imuError || wifiError){
  
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
  
      chargeMode = (digitalRead(chargeModePin) == HIGH);
      programMode = (digitalRead(programModePin) == LOW);
      imuError = !drive.checkSensors();
      wifiError = !wifi.checkWifi();
      
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
      
      chargeMode = (digitalRead(chargeModePin) == HIGH);
      programMode = (digitalRead(programModePin) == LOW);
      imuError = !drive.checkSensors();
      wifiError = !wifi.checkWifi();
      
    }
    while(imuError){
      stopRobot();
      digitalWrite(ledPin, HIGH);
      delay(250);
      digitalWrite(ledPin, LOW);
      delay(250);
      digitalWrite(ledPin, HIGH);
      delay(1000);
      digitalWrite(ledPin, LOW);
      delay(1000);
      chargeMode = (digitalRead(chargeModePin) == HIGH);
      programMode = (digitalRead(programModePin) == LOW);
      imuError = !drive.checkSensors();
      wifiError = !wifi.checkWifi();
    }
    while(wifiError){
      stopRobot();
      int ledPin = 13;
      digitalWrite(ledPin, HIGH);
      delay(1000);
      digitalWrite(ledPin, LOW);
      delay(1000);
      //Wait for AT response is enough delay
      if(wifi.checkWifi()){
        wifi.setup();
      }
      chargeMode = (digitalRead(chargeModePin) == HIGH);
      programMode = (digitalRead(programModePin) == LOW);
      imuError = !drive.checkSensors();
      wifiError = !wifi.checkWifi();
    }
  }
  startRobot();
}

void checkActions(){
  checkMode();
}

void periodicFast(){
  
}

TimedAction checkThread = TimedAction(100, checkActions);
TimedAction fastActions = TimedAction(10, periodicFast);
TimedAction threads[] = {checkThread, fastActions};

void periodic(){
  for(int i = 0; i < sizeof(threads); i++){
    threads[i].check();
  }
}

void setup() {

  pinMode(programModePin, INPUT_PULLUP);
  pinMode(chargeModePin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  wifi.setup();
  drive.setup(periodic);
  ultrasonic.setup(periodic);
  checkMode();
  startRobot();
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

void begin(){
  ultrasonic.setViewAngle(0);
}

void autonomous(){
  drive.driveSpeed(255);
}

void startRobot(){
  begin();
  autonomous();
}
