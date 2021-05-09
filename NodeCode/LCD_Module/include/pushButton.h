//**************************************************
// File: pushButton.h
// Author: Isaac Wittmeier
// Description: Reads a pushbutton input
//**************************************************
#include <Arduino.h>
#include "pinMaps.h"
#include "gpioRead.h"

//initializes the pushbutton module
void InitPushButton();

//updates state and returns true if state changed
bool PushButtonRead(String* state);