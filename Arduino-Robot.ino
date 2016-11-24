#include <TimedAction.h>

#include "RobotDrive.h"
#include "RobotUltrasonic.h"
#include "RobotWifi.h"

int programModePin = 31;
int chargeModePin = 33;
int ledPin = 13;

RobotDrive drive;
RobotUltrasonic ultrasonic;
RobotWifi wifi;

TimedAction checkThread = TimedAction(500, checkMode);

void setup() {

  pinMode(programModePin, INPUT_PULLUP);
  pinMode(chargeModePin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  startRobot();
  //wifi.setup();
  
}

void loop() {
  checkThread.check();
  //Do Stuff based on WiFi messages here
}

void checkMode(){

  boolean chargeMode = (digitalRead(chargeModePin) == HIGH);
  boolean programMode = (digitalRead(programModePin) == LOW);

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
  
      chargeMode = (digitalRead(chargeModePin) == HIGH);
      programMode = (digitalRead(programModePin) == LOW);
      
    }
  }
  startRobot();
}

void stopRobot(){
  drive.stopDrive();
  ultrasonic.stop();
  drive = null;
  ultrasonic = null;
}

void startRobot(){
  drive.setup(checkThread);
  ultrasonic.setup();
}

