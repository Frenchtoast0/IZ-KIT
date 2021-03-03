//**************************************************
// File: gpioRead.h
// Author: Isaac Wittmeier
// Description: Returns the states of GPIO pins
//**************************************************
#include <Arduino.h>

//initializes array of GPIO pins
//int pins[] - array of pins to init
//int numPins - amount of pins in list
//bool output - output or not
void GPIOSetup(int pins[], int numPins, bool output)
{
    //pins are input pins
    if (!output)
    {
        for (int i = 0; i < numPins; i ++)
        {
            pinMode(pins[i], INPUT);
        }
    }
    //pins are output pins
    else
    {
        for (int i = 0; i < numPins; i ++)
        {
            pinMode(pins[i], OUTPUT);
        }
    }
}

//returns the state of a GPIO pin 
//int pin - pin to read from
bool GPIORead(int pin){ return digitalRead(pin);}

//outputs high/low to GPIO
//int pin - pin to write to
//bool state - true == high, false == low
void GPIOWrite(int pin, bool state) 
{
    if (state) digitalWrite(pin, HIGH);
    else (digitalWrite(pin, LOW));
}
