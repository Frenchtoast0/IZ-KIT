//**************************************************
// File: Main.cpp
// Author: Isaac Wittmeier
// Description: Main program loop of NodeMCU board
//**************************************************
#include <Arduino.h>
#include "wificomms.h"
#include "pinMaps.h"

String ssid = "NodeMCU";  //wifi SSID
String pass = "passverd"; //wifi password

String server = "https://thor.net.nait.ca"; //server of node control
String url = "/~izkit/webservice.php";      //url on server to access

//runs once upon startup
void setup()
{
  //start serial communications
  Serial.begin(115200);

  //connect to wifi
  if (!WifiConnect(ssid, pass)) Serial.println("Wifi connection failed!");
}

//constantly repeats
void loop()
{
  //send post request
  Serial.println(SendPost_Result(server + url, "action=timeX"));

  //wait
  delay(5000);
}