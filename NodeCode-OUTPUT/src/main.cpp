//**************************************************
// File: Main.cpp
// Author: Isaac Wittmeier
// Description: Main program loop of an output NodeMCU board
//**************************************************
#include <Arduino.h>
#include "wificomms.h"
#include "pinMaps.h"

const int id = 000000001; //9 digit module id

float state = 0.0;     //state of output

String ssid = "NodeMCU";  //wifi SSID
String pass = "passverd"; //wifi password

String server = "https://thor.net.nait.ca"; //server of node control
String url = "/~izkit/svc/devices";      //url on server to access

//runs once upon startup
void setup()
{
  pinMode(D0, INPUT);

  //start serial communications
  Serial.begin(115200);

  //connect to wifi
  while (!WifiConnect(ssid, pass)) Serial.println("Wifi connection failed!");

  //register device with server
  Serial.println(SendPost_Result(server + url + "/register", "id=" + String(id) + "&state=" + String(state) + "&ip=" + String(0_0_0_0)));
}

//constantly repeats
void loop()
{


  //button: 1 means not pressed, 0 means pressed
  state = !digitalRead(D0);

  if (lastState != state)
  {
    //update state on server
    Serial.println(SendPost_Result(server + url + "/update", "id=" + String(id) + "&state=" + String(state)));
    lastState = state;
  }
}