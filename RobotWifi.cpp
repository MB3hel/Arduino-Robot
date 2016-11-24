#include "RobotWifi.h"
#include <ESP8266.h>
#include "Arduino.h"

ESP8266 espWifi(Serial2, 115200);

String apSSID = "ESP8266-Module";
String apPassword = "ESP-12_Dev";
String apIP = "10.33.30.1";
int port = 8090;
int errors = 0;
boolean fatal = false;

String RobotWifi::getMessage(){

  uint8_t buffer[128] = {0};
  uint8_t mux_id = -1;
  uint32_t len = espWifi.recv(&mux_id, buffer, sizeof(buffer), 100);
  
  if (len > 0) {
    
    String message = String((char*)buffer);

    return message;
                    
  }

  return "";
  
}

boolean setSoftAPIP(String ip){

  Serial2.print("AT+CIPAP_CUR=\"");
  Serial2.print(apIP);
  Serial2.println("\"");
  String response = "";
  delay(500); //Wait for response to be ready and buffered
  while(Serial2.available()){
    response += String((char)Serial2.read());
  }

  if(response.indexOf("OK") != -1){
    return true;
  }else{
    return false;
  }
  
}

void RobotWifi::setup(){
  
  if(!espWifi.setOprToSoftAP()){

    fatal = true;
    errors++;
    
  }

  int connections = 0;
  boolean a = false;
  boolean b = false;

  if(espWifi.setSoftAPParam(apSSID, apPassword))
    a = true;
  else
    errors++;

  if(setSoftAPIP(apIP))
    b = true;
  else
    errors++; 

  if(a && b)
    connections++;

  if(!connections > 0){

    fatal = true;
    errors++;
    
  }

  if (!espWifi.enableMUX()) {
    
    if(connections > 1)
      fatal = true;

    errors++;
    
  }

  if(!espWifi.startTCPServer(port)){
    
    fatal = true;
    errors++;
    
  }

  if(!espWifi.setTCPServerTimeout(10))
    errors++;

  int ledPin = 13;
  
  while(1){

    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    delay(1000);
    
  };
  
}


