//**************************************************
// File: wificomms.h
// Author: Isaac Wittmeier
// Description: Connects NodeMCU to wifi network
//              and allows for data communication
//**************************************************
#include <Arduino.h>

//Starts wifi connection with
//specified ssid and password
bool WifiConnect(String ssid, String password);

//Sends a string of http
//data via POST and returns result
String SendPost_Result(String url, String data);

//Sends a string of http
//data via POST and returns success or fail
bool SendPost(String url, String data);
