#include <Arduino.h>
#include "ESP8266WiFi.h" 
#include "ESP8266HTTPClient.h"
#include "pinMaps.h"

const char* ssid = "NodeMCU";  //wifi SSID
const char* pass = "passverd"; //wifi password


const char* server = "google.ca";//"thor.net.nait.ca"; //server of node control
const int port = 80;//443; //port on server, 443=https, 80=http

WiFiClient client; //wifi connection holder

void setup() {
  //start serial communications
  Serial.begin(115200);

  //start wifi connection
  Serial.println("Attempting to connect to Wifi network...");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connected to wifi");

  //attempt to contact server
  Serial.println("Starting server connection...");
  
  if (client.connect(server, port))
  {
    Serial.println("Connected!");
    

    //String req = "GET /~izkit/httpTest.php HTTP/1.0\r\n";
    //req += "Host: thor.net.nait.ca";
    client.print("GET /search?sxsrf=ALeKk01y2phPwZbEUrsEXU4nLFGdoy5qbw%3A1612918277669&ei=BS4jYOCzKJHn-gSgwIWIBg&q=hello&oq=hello&gs_lcp=CgZwc3ktYWIQAzIKCC4QsQMQQxCTAjIECAAQQzIECC4QQzIECC4QQzIECC4QQzIECAAQQzIECAAQQzIFCAAQsQMyBAgAEEMyBQgAELEDOgQIIxAnOgoILhCxAxCDARBDULUWWPwbYN0daABwAHgAgAG9AYgB9ASSAQM1LjGYAQCgAQGqAQdnd3Mtd2l6wAEB&sclient=psy-ab&ved=0ahUKEwigyvfnjN7uAhWRs54KHSBgAWEQ4dUDCA0&uact=5 HTTP/1.0\r\n\r\n");
    //client.print("GET /~izkit/httpTest.php HTTP/1.1\r\n");
    //client.print("Host: thor.net.nait.ca\r\n\r\n");
    //make http request
    //client.print("GET /~izkit/httpTest.php HTTP/1.1\r\n");
    //client.print("Host: thor.net.nait.ca\r\n");
    //client.print("GET / HTTP/1.1\r\n");
    //client.print("Host: www.website.org\r\n");
    //Serial.println(client.write())
    //display response
    Serial.println(client.readString());
  }
  else Serial.println("Connection failed!");
}

void loop() {
  delay(10);
}