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

using namespace IZKit; //include device setup stuff

String state = "Initial"; //current state
Device dev(ID, state);

//runs once upon startup
void setup()
{
  //start serial communications
  Serial.begin(115200);

  InitLed();

  //setup device
  //dev.ConnectWifi("NodeMCU", "passverd", 0);
  //dev.AddInfo(Node_DESC, NODE_IO);
  //dev.SetValue(state, 0);
}

//constantly repeats
void loop()
{
  //respond based on state
  if (state == "ON") ledOn();
  if (state == "OFF" || state == "Initial") ledOff();

  //pause
  delay(10);

  delay(1000);

  if (state == "OFF" || state == "Initial") state = "ON";
  else if (state == "ON") state = "OFF";

  Serial.println(state);
}