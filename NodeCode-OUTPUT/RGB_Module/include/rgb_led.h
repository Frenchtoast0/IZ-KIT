//**************************************************
// File: rgb_led.h
// Author: Isaac Wittmeier
// Description: Controls the RGB led
//**************************************************
#include "pinMaps.h"
#include <Arduino.h>

//setup rgb led
void RGB_Init();

//decompose display string and display
//string length must be exactly 12 chars
//ie. "R001G255B125"
//returns bool - success or fail
bool RGB_Change(String value);