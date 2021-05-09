//**************************************************
// File: Main.cpp
// Author: Isaac Wittmeier
// Description: Main program loop of NodeMCU board
//**************************************************
#include <Arduino.h>
#include "pinMaps.h"
#include "config.h"
#include "lightSensor.h"
#include "analogRead.h"
#include "IzKit.h"

using namespace IzKit;

String state = "Initial"; //current state

Device dev(NODE_ID, NODE_IO);

//runs once upon startup
void setup()
{
  //start serial communications
  Serial.begin(115200);

  //setup device
  dev.ConnectWifi(WIFI_SSID, WIFI_PASS, 0);
  dev.addInfo(NODE_DESC);
}

//constantly repeats
void loop()
{
  //state changed, display 
  if (LightSensorRead(&state)) dev.setValue(state, 0);

  //pause
  delay(300);
}