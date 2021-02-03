#include <Arduino.h>
#include "ESP8266WiFi.h"
#include "pinMaps.h"

//copied from: https://www.arduino.cc/en/Reference/WiFiClient

char ssid[] = "NodeMCU";          //  your network SSID (name)
char pass[] = "passverd";   // your network password

int status = WL_IDLE_STATUS;
//IPAddress server(3,211,11,78); //http request dumper

char server[] = "httpbin.org";

// Initialize the client library
WiFiClient client;

void setup() {
  Serial.begin(115200);
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

    Serial.println("Connected to wifi");
    Serial.println("\nStarting connection...");
    // if you get a connection, report back via serial:
    if (client.connect(server, 80)) {
      Serial.println("connected");
      // Make a HTTP request:
      client.println("GET /anything HTTPS/1.0");
      client.println();

      Serial.println(client.readString());
    }
    else
    {
        Serial.println("Failed...");
    }
    
}

void loop() {
    delay(10);
}