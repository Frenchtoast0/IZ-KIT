//**************************************************
// File: led.h
// Author: Isaac Wittmeier
// Description: Outputs to an led
//**************************************************
#include <Arduino.h>
#include "pinMaps.h"
#include "gpio.h"

//initializes the led module
void InitLed();

//led controls
void ledOn();
void ledOff();