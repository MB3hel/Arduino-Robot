#include "Arduino.h"

class RobotUltrasonic{
  public:
    void setup();
    void stop();
    void setViewAngle(int angle);
    boolean ultrasonicInRange(int maxDistance);
    boolean ultrasonicInRange(int minDistance, int maxDistance);
};

