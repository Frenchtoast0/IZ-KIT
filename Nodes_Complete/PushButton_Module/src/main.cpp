//**************************************************
// File: Main.cpp
// Author: Isaac Wittmeier
// Description: Main program loop of NodeMCU board
//**************************************************
#include <Arduino.h>
#include "pinMaps.h"
#include "config.h"
#include "gpio.h"
#include "pushButton.h"
#include "IzKit.h"

using namespace IzKit;

String state = "Initial"; //current state

Device dev(NODE_ID, NODE_IO);

//runs once upon startup
void setup()
{
  //start serial communications
  Serial.begin(115200);

  InitPushButton();

  //setup device
  dev.ConnectWifi("NodeMCU", "passverd", 0);
  dev.addInfo(NODE_DESC);
  dev.setValue(state, 0);
}

//constantly repeats
void loop()
{
  //state changed
  if (PushButtonRead(&state)) dev.setValue(state, 0);

  //pause
  delay(10);
}