#include "RobotDrive.h"
#include "Arduino.h"

int leftEncoderPin = 18;
int rightEncoderPin = 19;
long left = 0;
long right = 0;

boolean RobotDrive::initSensors(){
  if(!accel.begin()){
    return false;
  }
  if(!mag.begin()){
    return false;
  }
  if(!gyro.begin()){
    return false;
  }
  return true;
}

byte RobotDrive::gyroRead8(byte reg){
  byte value;

  Wire.beginTransmission((byte)L3GD20_ADDRESS);
  #if ARDUINO >= 100
    Wire.write((uint8_t)reg);
  #else
    Wire.send(reg);
  #endif
  Wire.endTransmission();
  Wire.requestFrom((byte)L3GD20_ADDRESS, (byte)1);
  while (!Wire.available()); // Wait for data to arrive.
  #if ARDUINO >= 100
    value = Wire.read();
  #else
    value = Wire.receive();
  #endif  
  Wire.endTransmission();

  return value;
}
byte RobotDrive::magRead8(byte address, byte reg){
  byte value;

  Wire.beginTransmission(address);
  #if ARDUINO >= 100
    Wire.write((uint8_t)reg);
  #else
    Wire.send(reg);
  #endif
  Wire.endTransmission();
  Wire.requestFrom(address, (byte)1);
  #if ARDUINO >= 100
    value = Wire.read();
  #else
    value = Wire.receive();
  #endif  
  Wire.endTransmission();

  return value;
}
byte RobotDrive::accelRead8(byte address, byte reg){
  byte value;

  Wire.beginTransmission(address);
  #if ARDUINO >= 100
    Wire.write((uint8_t)reg);
  #else
    Wire.send(reg);
  #endif
  Wire.endTransmission();
  Wire.requestFrom(address, (byte)1);
  #if ARDUINO >= 100
    value = Wire.read();
  #else
    value = Wire.receive();
  #endif  
  Wire.endTransmission();

  return value;
}

boolean RobotDrive::checkSensors(){
  //Check for Accel
  uint8_t reg1_a = accelRead8(LSM303_ADDRESS_ACCEL, LSM303_REGISTER_ACCEL_CTRL_REG1_A);
  if (reg1_a != 0x57){
    return false;
  }
  //Check mag
  uint8_t reg1_m = magRead8(LSM303_ADDRESS_MAG, LSM303_REGISTER_MAG_CRA_REG_M);
  if (reg1_m != 0x10){
    return false;
  }
  uint8_t id = gyroRead8(GYRO_REGISTER_WHO_AM_I);
  //Serial.println(id, HEX);
  if ((id != L3GD20_ID) && (id != L3GD20H_ID)){
    return false;
  }
  return true;
}

void RobotDrive::waitForIMU(){
  int ledPin = 13;
  while(1){
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    delay(1000);
    if(initSensors()){
      break;
    }
  }
}

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

  checkThread = ct;

  attachInterrupt(digitalPinToInterrupt(leftEncoderPin), leftEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rightEncoderPin), rightEncoder, CHANGE);

  AFMS.begin();

  if(!initSensors()){
    waitForIMU();
  }
    
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
