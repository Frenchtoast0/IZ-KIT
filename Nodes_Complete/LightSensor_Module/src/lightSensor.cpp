//**************************************************
// File: lightSensor.cpp
// Author: Isaac Wittmeier
// Description: Allows for light sensor readings
//              Note: Runs on 3.3V
//**************************************************
#include <Arduino.h>
#include "lightSensor.h"

int light_sens = 5; //how much the light value has to differ from the 
                     //last state to be counted as a new value

//returns the light value as 
//a percentage from 0% to 100%
int LightValueRead()
{
    float voltage = VoltageRead(); //get analog voltage

    //convert voltage to range between 0-100
    float percentage = voltage * (100/(3.3));
    if (percentage < 0) percentage = 0;
    if (percentage > 100) percentage = 100;

    //invert percentage so bright is 100%
    percentage = 100 - percentage;

    //return without decimal places
    return (int)percentage;
}

//updates state and returns true if state changed
bool LightSensorRead(String* state)
{
    int light = LightValueRead(); //get new light intensity

    //state has changed
    if (*state == "Initial" || abs((*state).toDouble() - light) >= light_sens)
    {
        *state = String(light);
        return true;
    }
    else return false;
}