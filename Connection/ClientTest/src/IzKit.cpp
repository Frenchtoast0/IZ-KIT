#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "IzKit.h"

using namespace IzKit;

IPAddress Device::server(199,185,50,206);
int Device::port = 10001;
WiFiClient Device::client; //= WiFiClient();

//connectes to wifi 
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


Device::Device(char id,String value)
{
   this->id = id;
   this->value = value;
 
}

void Device::addInfo(String desc,int io)
{
   //cant register more then once
   if(regist) return;
   //register with device
    
   ConnectClient(1);
   Serial.println(id);
   //for some reason this would not work on one line
   client.print(id);
   client.println('|'+desc+'|'+io+'|'+value); 
   while(!client.available());
   regist = 1;
}

void Device::getUpdate(int v=0)
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

/*
forceably updates the server, note this 
dose not update the value
*/
void Device::setValue(String val, int v=0)
{
    if(!regist)
    {
        Serial.println("ERROR DEV HAS NO INFO IN DB");
        Serial.println("\tPlease run Device.addInfo()");
    }
    Serial.println("Connecting to client");
    ConnectClient(v);
    client.println(id);
    client.println(val);
    getUpdate(0);
    
    Serial.println("Value was changed to");
    Serial.println(value);
    
    
}
String Device::getValue()
{
    return value;
}

//TODO make a to string function
