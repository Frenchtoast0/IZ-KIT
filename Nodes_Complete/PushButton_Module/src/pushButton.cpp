//**************************************************
// File: pushButton.cpp
// Author: Isaac Wittmeier
// Description: Reads a pushbutton input
//**************************************************
#include <Arduino.h>
#include "pinMaps.h"
#include "pushButton.h"
#include "gpioRead.h"

//updates state and returns true if state changed
bool PushButtonRead(String* state)
{
    bool buttonState = GPIORead(D0); //get new button state
    String newState;                    //button state as a string

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