//**************************************************
// File: Main.cpp
// Author: Isaac Wittmeier
// Description: Main program loop of NodeMCU board
//**************************************************
#include <Arduino.h>
#include "pinMaps.h"
#include "config.h"
#include "gpioRead.h"
#include "pushButton.h"

String state = "Initial"; //current state

//runs once upon startup
void setup()
{
  //start serial communications
  Serial.begin(115200);

  Serial.println("done");
}

//constantly repeats
void loop()
{
  //state changed, display 
  if (PushButtonRead(&state)) Serial.println(state);

  //pause
  delay(10);
}