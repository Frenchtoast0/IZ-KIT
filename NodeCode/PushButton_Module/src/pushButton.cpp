//**************************************************
// File: pushButton.cpp
// Author: Isaac Wittmeier
// Description: Reads a pushbutton input
//**************************************************
#include <Arduino.h>
#include "pinMaps.h"
#include "pushButton.h"
#include "gpio.h"

//initialize pushbutton module
void InitPushButton()
{
    //initialize pin for input
    int pins[] = {D0};
    GPIOSetup(pins, 1, false);
}

//updates state and returns true if state changed
bool PushButtonRead(String* state)
{
    bool buttonState;              //get new button state
    bool debounceState;            //saved state to check for debounce
    String newState;               //button state as a string

    //first state
    debounceState = GPIORead(D0);

    delay(50);

    //second state
    buttonState = GPIORead(D0);

    //after delay, value is different, ignore debounce
    if (buttonState != debounceState) return false;

    //convert state to a string
    //has to be inverted
    if (buttonState) newState = "OFF";
    else newState = "ON";

    //state has changed
    if (*state == "Initial" || *state != newState)
    {
        *state = newState;
        return true;
    }
    else return false;
}