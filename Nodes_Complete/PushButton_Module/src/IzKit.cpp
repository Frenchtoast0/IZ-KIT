#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "IzKit.h"

using namespace IzKit;

IPAddress Device::server(199,185,50,206);
int Device::port = 10001;
WiFiClient Device::client;

void Device::ConnectWifi(const String ssid,const char* pass,int v = 0)
{
    WiFi.begin(ssid,pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        if(v) Serial.print(WiFi.status());
    }
    if(v) Serial.println("Connected to wifi");

}

void Device::ConnectClient(int v=0)
{
    if(!client.connected())
    {
        if(client.connect(server,port))
        {
            if(v)Serial.println("Connected to Server");
        }
        else
        {
            if(v)Serial.println("Error could not connect to server");
            Serial.println(server.toString());
            Serial.println(port);
        }
    }
}


Device::Device(String id,int io)
{
   this->id = id;
   this->io = io;
   this->value = "inital";
}

void Device::addInfo(String desc)
{
   if(regist) return;
   if(!client.connected())
   {
       ConnectClient(1);
       Serial.println(id+" adding info");
       client.print(id);
       client.println('|'+desc+'|'+(String)io);
       client.flush(); // needs to happen here
       Serial.println("Has been added");
       regist = 1;
   }
}

/*
    returns true if updated else it 
*/
int Device::CheckUpdate(int v=0)
{
    Serial.println("What the hell");
    if(!regist)
    {
        Serial.println("ERROR DEV HAS NO INFO IN DB");
        Serial.println("\tPlease run Device.addInfo()");
    }
    if(client.available())
    {
        this->value = client.readString();
        client.print("1");
        client.flush();
        return 1;
    }
    return 0;
}

void Device::setValue(String val, int v=0)
{
    if(!regist)
    {
        Serial.println("ERROR DEV HAS NO INFO IN DB");
        Serial.println("\tPlease run Device.addInfo()");
    }
    //only do this if the device is an input
    if(io)
    {
        //cleaing buffer 
        Serial.println("Sending Server value");
        client.println(val);
        value = val;
        Serial.println("Data has been sent");
    }
}

String Device::getValue()
{
    return value;
}

