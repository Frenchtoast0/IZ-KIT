//**************************************************
// File: izkit.cpp
// Author: Ezekiel Enns
// Description: Communications of IZ-Kit
//**************************************************
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "izkit.h"

using namespace IZKit;

IPAddress Device::server(199,185,50,206);
int Device::port = 10001;
WiFiClient Device::client;

void Device::ConnectWifi(const String ssid, String pass, int v = 0)
{
    WiFi.begin(ssid,pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        if(v) Serial.print(WiFi.status());
    }
    if(v) Serial.println("Connected to wifi");

}

void Device::ConnectClient(int v = 0)
{
    if(client.connect(server, port))
    {
        if(v) Serial.println("Connected to Server");
    }
    else
    {
        if(v) Serial.println("Error: could not connect to server");
        Serial.println(server.toString());
        Serial.println(port);
    }
}

Device::Device(String id, String value)
{
   this->id = id;
   this->value = value;
}

void Device::AddInfo(String desc, int io)
{
   if(regist) return;
    
   ConnectClient(1);
   Serial.println(id);
   client.print(id);
   client.println('|'+desc+'|'+io+'|'+value); 
   while(!client.available());
   regist = 1;
}

void Device::GetUpdate(int v = 0)
{
    if(!regist)
    {
        Serial.println("ERROR DEV HAS NO INFO IN DB");
        Serial.println("\tPlease run Device.addInfo()");
    }

    if(!this->client.connected())
    {
        ConnectClient(v);
        client.println(this->id+'|');
        client.println(this->value);
    }
    while(!client.available());
    this->value = client.readString();
}

void Device::SetValue(String val, int v = 0)
{
    if(!regist)
    {
        Serial.println("ERROR DEV HAS NO INFO IN DB");
        Serial.println("\tPlease run Device.addInfo()");
    }
    Serial.println("Connecting to client");
    ConnectClient(v);
    client.println(id);
    client.println('|'+val);
    GetUpdate(0);
    
    Serial.println("Value was changed to");
    Serial.println(value);
    
    
}

String Device::GetValue()
{
    return value;
}

