//**************************************************
// File: led.cpp
// Author: Isaac Wittmeier
// Description: Outputs to an led
//**************************************************
#include <Arduino.h>
#include "pinMaps.h"
#include "led.h"
#include "gpio.h"

//initialize led module
void InitLed()
{
    //initialize pin for output
    int pins[] = {D0};
    GPIOSetup(pins, 1, true);
}

//led controls
void ledOn()
{
    GPIOWrite(D0, HIGH);
}
void ledOff()
{
    GPIOWrite(D0, LOW);
}