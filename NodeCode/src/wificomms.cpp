//**************************************************
// File: wificomms.cpp
// Author: Isaac Wittmeier
// Description: Connects NodeMCU to wifi network
//              and allows for data communication
//**************************************************
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h> //allows for HTTPS
#include "wificomms.h"

BearSSL::WiFiClientSecure client; //for https connection
HTTPClient https;        //for http communications

//Starts wifi connection with
//specified ssid and password
//returns false if timeout
bool WifiConnect(String ssid, String password)
{
  int timeout = 10; //seconds maximum

  //start wifi connection
  WiFi.mode(WIFI_STA); //station mode, not AP
  WiFi.begin(ssid, password);

  //limit wait time
  for (; timeout > 0; timeout--) 
  {
    if (WiFi.status() == WL_CONNECTED) 
    {
      break;
    }
    delay(1000);
  }

  //connection timed out
  if (timeout == 0) return false;

  return true;
}

//Sends a string of http
//data via POST and returns result
String SendPost_Result(String url, String data)
{
  String result = "Post failed!"; //post result default

  //avoid any security, but still allow https communications
  client.setInsecure();

  //connect to server
  if (https.begin(client, url))
  {
    int httpCode; //return value of https request

    //send post request
    https.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = https.POST(data);

    //http did not error
    if (httpCode > 0)
    {
      //server responded A-OK
      if (httpCode == HTTP_CODE_OK)
      {
        result = https.getString();
      }
      else result = "Post failed: HttpCode:" + String(httpCode);
    }
    else result = "Post failed: HttpCode:" + String(httpCode);

    //clean up connection
    https.end();
  }

  return result;
}

//Sends a string of http
//data via POST and returns success or fail
bool SendPost(String url, String data)
{
  bool result = false; //post result default

  //avoid any security, but still allow https communications
  client.setInsecure();

  //connect to server
  if (https.begin(client, url))
  {
    int httpCode; //return value of https request

    //send post request
    https.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = https.POST(data);

    //http did not error
    if (httpCode > 0)
    {
      //server responded A-OK
      if (httpCode == HTTP_CODE_OK)
        result = true;
    }

    //clean up connection
    https.end();
  }

  return result;
}
