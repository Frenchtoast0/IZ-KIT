//**************************************************
// File: Main.cpp
// Author: Isaac Wittmeier
// Description: Main program loop of NodeMCU board
//**************************************************
#include <Arduino.h>
#include "wifiComms.h"
#include "pinMaps.h"
#include "config.h"

String state = "Initial"; //current state

String ssid = "NodeMCU";  //wifi SSID
String pass = "passverd"; //wifi password

String server = "https://thor.net.nait.ca"; //server of node control
String url = "/~izkit/svc/devices";      //url on server to access


//runs once upon startup
void setup()
{


  //start serial communications
  Serial.begin(115200);

  //connect to wifi
  while (!WifiConnect(ssid, pass)) Serial.println("Wifi connection failed!");

  //register device with server
  //Serial.println(SendPost_Result(server + url + "/register", "id=" + String(0) + "&state=" + String(state)));
}


//constantly repeats
/*void loop()
{
  //send post request
  //Serial.println(SendPost_Result(server + url, "id=" + String(id) + "&state=" + String(state)));

  //wait 100ms
  delay(100);

  //button: 1 means not pressed, 0 means pressed
  state = !digitalRead(D0);

  if (lastState != state)
  {
    //update state on server
    Serial.println(SendPost_Result(server + url + "/update", "id=" + String(id) + "&state=" + String(state)));
    lastState = state;
  }
}*/