#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
//add name sapce 
namespace IzKit
{
  class Device
  {
    private:
      //connection to socket server memebers
      static IPAddress server;  //the socket serve address
      static WiFiClient client; //client for connecting to server
      static int port;          //port socket server is on
      static char apiKey[];     //becuase ik Isaac wants this ;P
      //Connection to wifi and db
      char id;
      String value;
      static void ConnectClient(int);
      int regist = 0;

    public:
      static void ConnectWifi(const String ssid,const char* pass,int);
      
      //getters and setters
      int getId();
      void addInfo(String desc,int io);
      
      //sets a value and performs a blocking update
      void setValue(String,int);
      String getValue();

      void getUpdate(int);         //none blocking 
       
      Device(char id,String value);

  };
}