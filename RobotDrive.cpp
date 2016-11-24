#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include "RobotDrive.h"
#include "Arduino.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *Motor_Left_Front = AFMS.getMotor(4);
Adafruit_DCMotor *Motor_Right_Front = AFMS.getMotor(3);
Adafruit_DCMotor *Motor_Left_Rear = AFMS.getMotor(1);
Adafruit_DCMotor *Motor_Right_Rear = AFMS.getMotor(2);

int leftEncoderPin = 18;
int rightEncoderPin = 19;
long left = 0;
long right = 0;

TimedAction checkThread;

//Encoder counter functions
void leftEncoder(){

  left++;
  
}

void rightEncoder(){

  right++;
  
}

void resetLeft(){

  left = 0;
  
}

void resetRight(){

  right = 0;
  
}

//End encoder functions

void RobotDrive::setup(TimedAction ct){

  attachInterrupt(digitalPinToInterrupt(leftEncoderPin), leftEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rightEncoderPin), rightEncoder, CHANGE);

  checkThread = ct;
  
}

void RobotDrive::leftSpeed(int pwmSpeed){

  Motor_Left_Front->setSpeed(abs(pwmSpeed));
  Motor_Left_Rear->setSpeed(abs(pwmSpeed));
  
  if(pwmSpeed > 0){

    Motor_Left_Front->run(FORWARD);
    Motor_Left_Rear->run(FORWARD);
    
  }else if(pwmSpeed < 0){

    Motor_Left_Front->run(BACKWARD);
    Motor_Left_Rear->run(BACKWARD);
    
  }else{

    Motor_Left_Front->run(RELEASE);
    Motor_Left_Rear->run(RELEASE);
    
  }
  
}

void RobotDrive::rightSpeed(int pwmSpeed){

  Motor_Right_Front->setSpeed(abs(pwmSpeed));
  Motor_Right_Rear->setSpeed(abs(pwmSpeed));
  
  if(pwmSpeed > 0){

    Motor_Right_Front->run(BACKWARD);
    Motor_Right_Rear->run(BACKWARD);
    
  }else if(pwmSpeed < 0){

    Motor_Right_Front->run(FORWARD);
    Motor_Right_Rear->run(FORWARD);
    
  }else{

    Motor_Right_Front->run(RELEASE);
    Motor_Right_Rear->run(RELEASE);
    
  }
  
}

void RobotDrive::driveSpeed(int left, int right){

  leftSpeed(left);
  rightSpeed(right);
  
}

void RobotDrive::driveSpeed(int speed){

  leftSpeed(speed);
  rightSpeed(speed);
  
}

void RobotDrive::stopDrive(){

  leftSpeed(0);
  rightSpeed(0);
  
}

void RobotDrive::brakeDrive(int currentSpeed){

  leftSpeed(-1 * currentSpeed);
  rightSpeed(-1 * currentSpeed);
  delay(100);
  stopDrive();
  
}

void RobotDrive::brakeDrive(int currentLeft, int currentRight){

  leftSpeed(-1 * currentLeft);
  rightSpeed(-1 * currentRight);
  delay(100);
  stopDrive();
  
}

void RobotDrive::driveDistance(int centimeters, int speed, boolean brakeToStop){

  resetLeft();
  resetRight();
  
  double avg = 0;

  leftSpeed(speed);
  rightSpeed(speed);
  
  while(avg < ((centimeters / 21) * 40)){        //40 encoder ticks is about 21 cm

    checkThread.check();
    avg = (left + right) / 2;
    
  }

  if(!brakeToStop){

    stopDrive();
    
  }else{

    brakeDrive(speed);
    
  }
  
}

void RobotDrive::driveDistance(int centimeters, int left, int right, boolean brakeToStop){

  resetLeft();
  resetRight();
  
  double avg = 0;

  leftSpeed(left);
  rightSpeed(right);
  
  while(avg < ((centimeters / 21) * 40)){        //40 encoder ticks is about 21 cm
    checkThread.check();
    avg = (left + right) / 2;
    
  }

  if(!brakeToStop){

    stopDrive();
    
  }else{

    brakeDrive(left, right);
    
  }
  
}
