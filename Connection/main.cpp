#include "IzKit.h"
#include <Arduino.h>
#include <SPI.h>
#include <ESP8266WiFi.h>


//this namespace is required for using the object
using namespace IzKit;
//this is a constructor, takes id,value
Device dev("PSB-002",0);
int stop = 1;
void setup() {
  Serial.begin(115200);
  //example use of this code, read header for details
  dev.ConnectWifi("SHAW-178D20","25114C023072",1);
  //do once to set value, ONLY DO IF IT IS A INPUT, 1=INPUTS
  dev.setValue("123213",1);
  dev.addInfo("This Description Is a Example");
}

void loop() {
  //returns true if update, 
  if(dev.CheckUpdate(1) && stop)  //only do if dev is a output
  {
    Serial.println("REEEEE:"+dev.getValue());
    stop = 0;
  }
}
