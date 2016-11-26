#include "RobotWifi.h"
#include <ESP8266.h>
#include "Arduino.h"

RobotWifi::RobotWifi(){
  espWifi = new ESP8266(Serial2, 115200);
}

String RobotWifi::getMessage(){

  uint8_t buffer[128] = {0};
  uint8_t mux_id;
  uint32_t len = espWifi->recv(&mux_id, buffer, sizeof(buffer), 100);
  
  if (len > 0) {
    String message = String((char*)buffer);
    Serial.print("Message: ");
    Serial.println(message);
    espWifi->send(mux_id, buffer, len);
    return message;
  }

  return NO_MESSAGE;
  
}

boolean RobotWifi::setSoftAPIP(String ip){

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
  
  if(!espWifi->setOprToSoftAP()){

    fatal = true;
    errors++;
    
  }

  int connections = 0;
  boolean a = false;
  boolean b = false;

  if(espWifi->setSoftAPParam(apSSID, apPassword))
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

  if (!espWifi->enableMUX()) {
    
    if(connections > 1)
      fatal = true;

    errors++;
    
  }

  if(!espWifi->startTCPServer(port)){
    
    fatal = true;
    errors++;
    
  }

  if(!espWifi->setTCPServerTimeout(10))
    errors++;

  int ledPin = 13;
  
  while(fatal){

    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    delay(1000);

    if(espWifi->kick()){
      setup();
    }
    
  };
  
}

void checkConnection(){
  
}

