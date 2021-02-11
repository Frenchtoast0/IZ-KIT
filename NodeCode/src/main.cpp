/*#include <Arduino.h>
#include "ESP8266WiFi.h" 
#include "ESP8266HTTPClient.h"
#include "pinMaps.h"

const char* ssid = "NodeMCU";  //wifi SSID
const char* pass = "passverd"; //wifi password

const char* server = "thor.net.nait.ca"; //server of node control
const int port = 443; //port on server, 443=https, 80=http

WiFiClient client; //wifi connection holder
HTTPClient http;

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
    Serial.println(client.readString());
    Serial.println(client.remoteIP());


    Serial.println("Connected!");
    

    //String req = "GET /~iwittmei/CMPE-2500/ICAs/ica06/svc/messages HTTP/1.1";
    //req += "Host: thor.net.nait.ca\r\n";
    client.println("GET /~izkit HTTP/1.0");
    client.println("Host: thor.net.nait.ca");
    client.println();
    //client.print("Host: thor.net.nait.ca\r\n\r\n");
    //make http request
    //client.print(req);

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
}*/

/*#include <Arduino.h>
#include "ESP8266WiFi.h" 
#include "ESP8266HTTPClient.h"
#include "pinMaps.h"

const char* ssid = "NodeMCU";  //wifi SSID
const char* pass = "passverd"; //wifi password

const char* server = "thor.net.nait.ca"; //server of node control
const int port = 443; //port on server, 443=https, 80=http

BearSSL::WiFiClientSecure secure;

WiFiClient client; //wifi connection holder
HTTPClient http;

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
    Serial.println(client.readString());
    Serial.println(client.remoteIP());


    Serial.println("Connected!");
    

    //String req = "GET /~iwittmei/CMPE-2500/ICAs/ica06/svc/messages HTTP/1.1";
    //req += "Host: thor.net.nait.ca\r\n";
    client.println("GET /~izkit HTTP/1.0");
    client.println("Host: thor.net.nait.ca");
    client.println();
    //client.print("Host: thor.net.nait.ca\r\n\r\n");
    //make http request
    //client.print(req);

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
  delay(10);}*/

#include <Arduino.h>
#include "ESP8266WiFi.h" 
#include <WiFiClientSecure.h>
#include "ESP8266HTTPClient.h"
#include "pinMaps.h"

const char* ssid = "NodeMCU";  //wifi SSID
const char* pass = "passverd"; //wifi password

String server = "thor.net.nait.ca"; //server of node control
String url = "/~iwittmei/CMPE-2500/ICAs/ica06/svc/messages"; //url on server
const int port = 443; //port on server, 443=https, 80=http

WiFiClientSecure client; //wifi connection holder

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

  client.setInsecure();
  //client.setFingerprint("b7 c1 5b 2d e8 15 15 46 1c 34 62 43 e3 b6 ae c2 60 e6 06 71");
  if (client.connect(server, port))
  {
    Serial.println("Connected!");

    HTTPClient http;
    http.begin("https://thor.net.nait.ca/~iwittmei/CMPE-2500/ICAs/ica06/svc/messages"); 
    http.addHeader("Content-Type", "application/json"); 
    http.addHeader("Cookie:", "PHPSESSID=a2acbb20826a65819f1b68df22402562");
    String postData = "message=testingstuff"; 
    auto httpCode = http.POST("{\"message\": \"Henry\" }"); 
    Serial.println(httpCode); //Print HTTP return code
    http.writeToStream(&Serial);
    http.end();

    /*client.println("POST " + url + " HTTP/1.1");
    client.print("Host: "); client.println(server);
    client.println("User-Agent: arduino 1.0");
    client.println("");
    
    while (client.available())
    {
      char c = client.read();
      Serial.print(c);
    }*/
    

    //http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    //http.setURL("https://thor.net.nait.ca/~izkit/httpTest.php");
    //http.sendRequest("GET", "https://thor.net.nait.ca/~izkit/httpTest.php");
    //Serial.println(http.GET());
    //Serial.println(http.getString());

    //Serial.println(http.setURL("https://thor.net.nait.ca/~izkit/httpTest.php"));
    //Serial.println(http.GET());
    //Serial.println(http.getString());

    Serial.println("done");
  }
  else Serial.println("Connection failed!");
}

void loop() {
  delay(10);
}