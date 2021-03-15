/*
#include <Arduino.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include "IzKit.h"

//working
char ssid[] = "SHAW-178D20";
char pass[] = "25114C023072";
char buff[] = "for here i am sitting on a tin can far above the world";
char val;       //value read
int i = 0;      //itterator
WiFiClient client;
IPAddress server(199,185,50,206);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("atempting to connect");
  pinMode(0,OUTPUT);
  //WiFi.mode(WIFI_STA); //station mode, not AP
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
  Serial.println(WiFi.localIP());
  Serial.println("Attempting to chat");
  if (client.connect(server, 10001))
  {
    Serial.println("connected");
    client.println("im another bio");
  }
  else{
    Serial.println("couldnt connect");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(client.available()){
    val = client.read();
    Serial.print(val);
  }
  else{
     client.println("for here im sitting in a tin can far above the world\n planet earth is blue\n");
  }
}
*/