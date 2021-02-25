//**************************************************
// File: Main.cpp
// Author: Isaac Wittmeier
// Description: Main program loop of NodeMCU board
//**************************************************
#include <Arduino.h>
#include "wificomms.h"
#include "pinmaps.h"
#include "config.h"

float lastState = 0.0; //saved to check for state change
float state = 0.0;     //current state

String ssid = "NodeMCU";  //wifi SSID
String pass = "passverd"; //wifi password

String server = "https://thor.net.nait.ca"; //server of node control
String url = "/~izkit/svc/devices";      //url on server to access

/*
//runs once upon startup
void setup()
{
  //initialize input pin
  pinMode(D0, INPUT);

  //start serial communications
  Serial.begin(115200);

  //connect to wifi
  while (!WifiConnect(ssid, pass)) Serial.println("Wifi connection failed!");

  //register device with server
  //Serial.println(SendPost_Result(server + url + "/register", "id=" + String(0) + "&state=" + String(state)));
}


//constantly repeats
void loop()
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
}
*/

void setup()
{
  //start serial communications
  Serial.begin(115200);

  //initialize analog input
  pinMode(A0, INPUT);
}

//analog sensor testing
void loop()
{
  int analog = analogRead(A0);
  float voltage = analog * (3.3/1024.0); //0->3.3 => 0->1024

  Serial.println(String(voltage) + "V");
  delay(10);
}