#include "Arduino.h"
#include <TimedAction.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_9DOF.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

class RobotDrive{
    Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
    Adafruit_DCMotor *Motor_Left_Front = AFMS.getMotor(4);
    Adafruit_DCMotor *Motor_Right_Front = AFMS.getMotor(3);
    Adafruit_DCMotor *Motor_Left_Rear = AFMS.getMotor(1);
    Adafruit_DCMotor *Motor_Right_Rear = AFMS.getMotor(2);
    
    Adafruit_9DOF dof = Adafruit_9DOF();
    Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
    Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(30302);
    Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);

    void (*periodicCallback)();
    
  public:
    void setup(void (*periodicCallback)());
    void leftSpeed(int pwmSpeed);
    void rightSpeed(int pwmSpeed);
    void driveSpeed(int left, int right);
    void driveSpeed(int speed);
    void stopDrive();
    void brakeDrive(int currentSpeed);
    void brakeDrive(int currentLeft, int currentRight);
    void driveDistance(int centimeters, int speed, boolean brakeToStop);
    void driveDistance(int centimeters, int left, int right, boolean brakeToStop);
    boolean checkSensors();
  private:
    boolean initSensors();
    byte gyroRead8(byte reg);
    byte magRead8(byte address, byte reg);
    byte accelRead8(byte address, byte reg);
};

