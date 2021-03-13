#include "IzKit.h"
#include <Arduino.h>
#include <SPI.h>
#include <ESP8266WiFi.h>


//working
using namespace IzKit;
int w = 1;
//yes tecnically you can have mutiple devices
Device dev('5',"on");

void setup() {
  Serial.begin(115200);
  //a static helper to let you connect to wifi
  dev.ConnectWifi("SHAW-178D20","25114C023072",1);
  dev.addInfo("Danky is best boi",1);
  //dev.setValue("TEST",1);
  Serial.println(dev.getValue());
}

void loop() {

  if(w) // 0 dosent make it flase 
  {
    Serial.println("HELLO WORLd");
    w=0;
  }
}
