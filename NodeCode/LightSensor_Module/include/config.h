//**************************************************
// File: config.h
// Author: Isaac Wittmeier
// Description: Values specific to node
//**************************************************
#define NODE_IO 1               //whether the node is an input(1) or an output(0)
#define NODE_Name "lightSensor"  //what kind of node it is

//description of node functionality
#define NODE_DESC "Node returns value 0-100 based on relative light levels"

//unique ID specific to this node only
#define NODE_ID "LTS-001"

//wifi login values
#define WIFI_SSID "NodeMCU"
#define WIFI_PASS "passverd"