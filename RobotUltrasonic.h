#include "Arduino.h"
#include <TimedAction.h>

class RobotUltrasonic{
  TimedAction checkThread = TimedAction(0, NULL);
  public:
    void setup(TimedAction ct);
    void stop();
    void setViewAngle(int angle);
    boolean ultrasonicInRange(int maxDistance);
    boolean ultrasonicInRange(int minDistance, int maxDistance);
};

