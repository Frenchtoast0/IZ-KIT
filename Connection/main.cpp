#include "IzKit.h"
#include <Arduino.h>
#include <SPI.h>
#include <ESP8266WiFi.h>


//this namespace is required for using the object
using namespace IzKit;
//this is a constructor, takes id,value
Device dev('5',"on");

void setup() {
  Serial.begin(115200);
  //example use of this code, read header for details
  dev.ConnectWifi("SHAW-178D20","25114C023072",1);
  dev.addInfo("This Description Is a Example",1);
  dev.setValue("off",1);
  Serial.println(dev.getValue());
}

void loop() {
}
