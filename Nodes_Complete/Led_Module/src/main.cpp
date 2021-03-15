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

String state = "Initial"; //current state

//runs once upon startup
void setup()
{
  //start serial communications
  Serial.begin(115200);

  InitLed();
}

//constantly repeats
void loop()
{
  //respond based on state
  if (state == "ON") ledOn();
  if (state == "OFF" || state == "Initial") ledOff();

  //pause
  delay(10);

  delay(100);

  if (state == "OFF" || state == "Initial") state = "ON";
  if (state == "ON") state = "OFF";
}