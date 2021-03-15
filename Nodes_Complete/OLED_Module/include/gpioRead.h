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
void GPIOSetup(int pins[], int numPins, bool output);

//returns the state of a GPIO pin 
//int pin - pin to read from
bool GPIORead(int pin);

//outputs high/low to GPIO
//int pin - pin to write to
//bool state - true == high, false == low
void GPIOWrite(int pin, bool state);
