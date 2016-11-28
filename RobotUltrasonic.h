#include "Arduino.h"
#include <TimedAction.h>

class RobotUltrasonic{
  void (*periodicCallback)();
  public:
    void setup(void (*periodicCallback)());
    void stop();
    void setViewAngle(int angle);
    boolean ultrasonicInRange(int maxDistance);
    boolean ultrasonicInRange(int minDistance, int maxDistance);
};

