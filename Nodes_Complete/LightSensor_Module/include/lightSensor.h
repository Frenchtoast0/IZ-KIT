//**************************************************
// File: lightSensor.h
// Author: Isaac Wittmeier
// Description: Allows for light sensor readings
//              Note: Runs on 3.3V
//**************************************************
#include <Arduino.h>
#include "analogRead.h"

//updates state and returns if state changed
bool LightSensorRead(String* state);