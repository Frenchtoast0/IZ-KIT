#include <Arduino.h>
#include "ESP8266WiFi.h"
#include "pinMaps.h"

WiFiServer server(80); //server on port 80, global instance

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(D2, OUTPUT);

  WiFi.mode(WIFI_AP); //turn into access point
  WiFi.softAP("NodeMCU", "passvord"); // SSID/password
  server.begin(); //start server


  //serial communications
  Serial.println("STARTING...");
  IPAddress HTTPS_ServerIP = WiFi.softAPIP(); //get server ip
  Serial.print("Server IP:");
  Serial.println(HTTPS_ServerIP);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(D2, HIGH);

  WiFiClient client = server.available();
  if (!client) return;
  Serial.println("Someone has connected!!!");
}