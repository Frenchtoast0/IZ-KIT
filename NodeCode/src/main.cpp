//**************************************************
// File: Main.cpp
// Author: Isaac Wittmeier
// Description: Main program loop of NodeMCU board
//**************************************************
#include <Arduino.h>
#include "wificomms.h"
#include "pinMaps.h"

const int id = 000000001; //9 digit module id

float lastState = 0.0; //saved to check for state change
float state = 0.0;     //current state

String ssid = "NodeMCU";  //wifi SSID
String pass = "passverd"; //wifi password

String server = "https://thor.net.nait.ca"; //server of node control
String url = "/~izkit/webservice.php";      //url on server to access

//runs once upon startup
void setup()
{
  pinMode(D0, INPUT);

  //start serial communications
  Serial.begin(115200);

  //connect to wifi
  if (!WifiConnect(ssid, pass)) Serial.println("Wifi connection failed!");
}

//constantly repeats
void loop()
{
  //send post request
  //Serial.println(SendPost_Result(server + url, "id=" + String(id) + "&state=" + String(state)));

  //wait 10s
  //delay(10000);

  //button: 1 means not pressed, 0 means pressed
  state = !digitalRead(D0);

  if (lastState != state)
  {
    //alert server
    Serial.println(SendPost_Result(server + url, "id=" + String(id) + "&state=" + String(state)));
    lastState = state;
  }
}