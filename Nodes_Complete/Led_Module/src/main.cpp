//**************************************************
// File: Main.cpp
// Author: Isaac Wittmeier
// Description: Main program loop of NodeMCU board
//**************************************************
#include <Arduino.h>
#include "pinMaps.h"
#include "config.h"
#include "gpio.h"
#include "led.h"
#include "izkit.h"

using namespace IzKit; //include device setup stuff

String state = "Initial"; //current state
Device dev(NODE_ID, NODE_IO);

//runs once upon startup
void setup()
{
  //start serial communications
  Serial.begin(115200);

  InitLed();

  //setup device
  dev.ConnectWifi("NodeMCU", "passverd", 0);
  dev.addInfo(NODE_DESC);
}

//constantly repeats
void loop()
{
  //check for new info
  if (dev.CheckUpdate(0))
  {
    String newState;
    newState = dev.getValue();

    //make sure valid state
    if (newState == "ON" || newState == "OFF")
      state = newState;

    //respond based on state
    if (state == "ON") ledOn();
    if (state == "OFF" || state == "Initial") ledOff();
  }

  delay(1000);
  Serial.println(state);
}