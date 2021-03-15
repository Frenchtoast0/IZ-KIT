/*
//**************************************************
// File: Main.cpp
// Author: Isaac Wittmeier
// Description: Main program loop of NodeMCU board
//**************************************************
#include <Arduino.h>
#include "pinMaps.h"
#include "config.h"

String state = "Initial"; //current state

//runs once upon startup
void setup()
{
  //start serial communications
  Serial.begin(115200);

}

//constantly repeats
void loop()
{

  //pause
  delay(10);
}*/