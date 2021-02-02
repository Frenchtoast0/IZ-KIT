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

  digitalWrite(D2, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  

  WiFiClient client = server.available();
  if (!client) return;
  Serial.println("Someone has connected!!!");

  String request = client.readStringUntil('\r');

  if (request.indexOf("/OFF") != -1){
    digitalWrite(D2, LOW); }
  else if (request.indexOf("/ON") != -1){
    digitalWrite(D2, HIGH);
  }

  //setup html page
  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML><html><input type=\"button\" value=\"Turn ON\" onclick=\"location.href='/ON'\">";
  s += "<!DOCTYPE HTML><html><input type=\"button\" value=\"Turn OFF\" onclick=\"location.href='/OFF'\">";
  s += "</html>";

  //serve html document to browser
  client.flush(); //clear previous stream info
  client.print(s); //send page
}