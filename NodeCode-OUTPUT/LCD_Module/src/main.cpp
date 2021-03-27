//**************************************************
// File: Main.cpp
// Author: Isaac Wittmeier
// Description: Main program loop of NodeMCU board
//**************************************************
#include <Arduino.h>
#include "pinMaps.h"
#include "config.h"
#include "i2c_lcd.h"

String state = "Initial"; //current state

//runs once upon startup
void setup()
{
  //start serial communications
  Serial.begin(115200);

  //setup lcd module
  LCD_Init();


  
  LCD_Display("32 character length");
}

//constantly repeats
void loop()
{ 
  
  //pause
  delay(500);
}