//**************************************************
// File: analogRead.h
// Author: Isaac Wittmeier
// Description: Allows for analog voltage readings
//              Note: Runs on 3.3V
//**************************************************
#include <Arduino.h>

//initializes analog reading
void AnalogSetup();

//reads analog value
int AnalogRead(); 

//reads an analog voltage
float VoltageRead();