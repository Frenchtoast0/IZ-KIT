#include <Arduino.h>
#include <SPI.h>
#include <ESP8266WiFi.h>

//working
char ssid[] = "************";
char pass[] = "************";

//message we send to server
char buff[] = "for here i am sitting on a tin can far above the world";

//byte we read from sever
char val;       

//this is our wificlient object
WiFiClient client;

//this is our ipAddress object, this will change to our server... just gotta hope that works
IPAddress server(192,168,0,20); //there should be a way to just throw our domain or something in there idk

void setup() {
  //going with standard baud
  Serial.begin(115200);
  Serial.println("atempting to connect");
  
  WiFi.begin(ssid, pass);
  
  //these dots kept my sainity
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
  //printing the ip we get from wifi to make sure its working
  Serial.println(WiFi.localIP());
  
  Serial.println("Attempting to chat");
  //this takes a ipAddress object, and the port
  if (client.connect(server, 8080)) 
  {
    /*
      now if we connect to the server on port 80(what ever port https is on)
      we maybe able to send get requests and read them havent checked yet will later tho
    */
    Serial.println("connected");
  }
  else{
    Serial.println("couldnt connect");
  }
}

void loop() {
  //client.available checks if data is coming from server, this will be false otherwise
  if(client.available()){
    //if data is coming in we read it into a byte
    val = client.read();
    Serial.print(val);
  }
  else{
    //now this is how we send data back to server, in one example i found (linked in doc) they sent a getrequest but it was on port 8000 not port 80
    //so i hope we can bypass the whole php stuff but thats a hope and most likly isnt how it works 
     client.println("for here im sitting in a tin can far above the world\n planet earth is blue\n");
  }
}
