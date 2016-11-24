#include "Arduino.h"
#include <TimedAction.h>

class RobotUltrasonic{
  TimedAction checkThread = TimedAction(0, NULL);
  public:
    void setup();
    void stop();
    void setViewAngle(int angle);
    boolean ultrasonicInRange(int maxDistance);
    boolean ultrasonicInRange(int minDistance, int maxDistance);
    RobotUltrasonic(TimedAction ct);
};

