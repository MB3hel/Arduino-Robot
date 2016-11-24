#include "Arduino.h"

class RobotDrive{
  public:
    void setup(TimedAction checkThread);
    void leftSpeed(int pwmSpeed);
    void rightSpeed(int pwmSpeed);
    void driveSpeed(int left, int right);
    void driveSpeed(int speed);
    void stopDrive();
    void brakeDrive(int currentSpeed);
    void brakeDrive(int currentLeft, int currentRight);
    void driveDistance(int centimeters, int speed, boolean brakeToStop);
    void driveDistance(int centimeters, int left, int right, boolean brakeToStop);
};

