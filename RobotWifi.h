#include "Arduino.h"
#include <TimedAction.h>
#include <ESP8266.h>

class RobotWifi{
    ESP8266* espWifi;
    String apSSID = "MarcusRobot";
    String apPassword = "ESP-12_Dev";
    String apIP = "10.33.30.1";
    int port = 8090;
    int errors = 0;
    boolean fatal = false;
    String NO_MESSAGE = "[NO_MESSAGE]";
  public:
    void setup();
    String getMessage();
    boolean checkWifi();
    void waitForWifi();
    RobotWifi();
   private:
    boolean setSoftAPIP(String ip);
};

