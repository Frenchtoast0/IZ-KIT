//**************************************************
// File: Main.cpp
// Author: Isaac Wittmeier
// Description: Main program loop of NodeMCU board
//**************************************************
#include <Arduino.h>
#include "pinMaps.h"
#include "config.h"
#include "IzKit.h"
#include "i2c_lcd.h"

using namespace IzKit; //include device setup stuff

String state = "Initial"; //current state
Device dev(NODE_ID, NODE_IO);

//runs once upon startup
void setup()
{
  //start serial communications
  Serial.begin(115200);

  //setup lcd module
  LCD_Init();

  //setup device
  dev.ConnectWifi(WIFI_SSID, WIFI_PASS, 0);
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

    //check if state is new
    if (newState != state)
    {
      state = newState;

      //show empty display
      if (state == "Disconnected" || state == "Initial")
      {
        LCD_Display("");
      }
      else
      {
        LCD_Display(state);
      }
    }
  }

  //pause
  delay(10);
}