#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

namespace IzKit
{
  class Device
  {
    private:
      //static memebers
      static IPAddress server;          //the socket serve address
      static WiFiClient client;         //client for connecting to server
      static int port;                  //port socket server is on
      static void ConnectClient(int v); //static function for connecting to socket Server
      
      //private memebers
      /*
        the reason these are private is becuase changing them will 
        mess up communication with server
      */
      char id;                          //Device ID on socket server            
      String value;                     //value Device has 
      int regist = 0;                   //Determins if device is registered in server

    public:
      //hadning function for connecting to a network take it or leave it 
      static void ConnectWifi(const String ssid,const char* pass,int);
      
      //self explanatory
      int getId();

      //registers device, this info is only saved on server since you shouldnt be changing it  
      void addInfo(String desc,int io);
      
      //[BLOCKING] sets the value of device and value on server, updates from server overide value
      // will not run untill addInfo() is called
      void setValue(String,int v);
      
      //simply outputs device value (not from server)
      String getValue();

      //[BLOCKING] sets value to current server state
      //will not run untill addInfo() is called
      void getUpdate(int v);          
      
      //constructor 
      Device(char id,String value);

      /* Things to note
            all communcation with server is blocking 
            due to travel time of packets to server
            so all functions that communicate with server
            block on the server untill it gets its value from the server
            this rule excludes ConnectClient since it has a seprate purpose

            there is also no error checking so if the connection 
            throws errors on the servers end the device will 
            permanently block, since if there was a 
            issue proceeding may not be useful, 
            the server on the other hand will still work
            and can accpet another connection
            
      */

  };
}
