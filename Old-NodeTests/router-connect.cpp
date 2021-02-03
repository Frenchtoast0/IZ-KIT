#include <Arduino.h>
#include "ESP8266WiFi.h"
#include "pinMaps.h"

const char* SSID = "NodeMCU"; //wifi SSID
const char* wifiPass = "passverd"; //wifi password

void setup() {

    Serial.begin(115200);

    pinMode(D2, OUTPUT);
    digitalWrite(D2, HIGH);

    //connect to network
    WiFi.begin(SSID, wifiPass);

    while (WiFi.status() != WL_CONNECTED) delay(500); //wait until connection

    Serial.println("Connected");
    Serial.println(WiFi.localIP()); //display ip address

}

void loop() {
  
}