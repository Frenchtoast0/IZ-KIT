//**************************************************
// File: izkit.h
// Author: Ezekiel Enns
// Description: Communications of IZ-Kit
//**************************************************
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

namespace IZKit
{
  class Device
  {
    private:
      //static memebers
      static IPAddress server;          //the socket serve address
      static WiFiClient client;         //client for connecting to server
      static int port;                  //port socket server is on
      static void ConnectClient(int v); //static function for connecting to socket Server
      
      //private members
      /*
        the reason these are private is becuase changing them will 
        mess up communication with server
      */
      String id;                          //Device ID on socket server            
      String value;                     //Value Device has 
      int regist = 0;                   //Determines if device is registered in server

    public:
      //function for connecting to a network take it or leave it, v=verbose 
      static void ConnectWifi(const String ssid, String pass, int v);
      
      //self explanatory
      int GetId();

      //registers device, this info is only saved on server since you shouldnt be changing it  
      void AddInfo(String desc, int io);
      
      //[BLOCKING] sets the value of device and value on server, updates from server overide value
      // will not run until AddInfo() is called
      void SetValue(String, int v);
      
      //simply outputs device value (not from server)
      String GetValue();

      //[BLOCKING] sets value to current server state
      //will not run untill AddInfo() is called
      void GetUpdate(int v);          
      
      //constructor 
      Device(String id, String value);

      /* Things to note
            all communication with server is blocking 
            due to travel time of packets to server
            so all functions that communicate with server
            block on the server until it gets its value from the server
            this rule excludes ConnectClient since it has a separate purpose

            there is also no error checking so if the connection 
            throws errors on the servers end the device will 
            permanently block, since if there was a 
            issue proceeding may not be useful, 
            the server on the other hand will still work
            and can accept another connection    
      */

  };
}
