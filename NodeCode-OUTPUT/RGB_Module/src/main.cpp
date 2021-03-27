//**************************************************
// File: Main.cpp
// Author: Isaac Wittmeier
// Description: Main program loop of NodeMCU board
//**************************************************
#include <Arduino.h>
#include "pinMaps.h"
#include "config.h"
#include "rgb_led.h"

String state = "Initial"; //current state

//runs once upon startup
void setup()
{
  //start serial communications
  Serial.begin(115200);

  //setup rgb module
  RGB_Init();
}

//constantly repeats
void loop()
{ 
  if (RGB_Change("R000G000B000")) Serial.println("Good");
  else Serial.println("Bad");
  
  //pause
  delay(1000);

  if (RGB_Change("R255G255B255")) Serial.println("Good");
  else Serial.println("Bad");

  delay(1000);

  if (RGB_Change("R255G000B255")) Serial.println("Good");
  else Serial.println("Bad");

  delay(1000);
}