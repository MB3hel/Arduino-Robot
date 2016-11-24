#include "Arduino.h"
#include <TimedAction.h>

class RobotDrive{
    TimedAction checkThread = TimedAction(0, NULL);
  public:
    void setup();
    void leftSpeed(int pwmSpeed);
    void rightSpeed(int pwmSpeed);
    void driveSpeed(int left, int right);
    void driveSpeed(int speed);
    void stopDrive();
    void brakeDrive(int currentSpeed);
    void brakeDrive(int currentLeft, int currentRight);
    void driveDistance(int centimeters, int speed, boolean brakeToStop);
    void driveDistance(int centimeters, int left, int right, boolean brakeToStop);
    RobotDrive(TimedAction ct);
};

