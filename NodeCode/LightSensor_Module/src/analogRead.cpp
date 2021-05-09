//**************************************************
// File: analogRead.cpp
// Author: Isaac Wittmeier
// Description: Allows for analog voltage readings
//              Note: Runs on 3.3V
//**************************************************
#include <Arduino.h>
#include "analogRead.h"

//initializes analog reading
void AnalogSetup() { pinMode(A0, OUTPUT); }

//reads analog value
int AnalogRead() { return analogRead(A0); }

//reads an analog voltage
float VoltageRead()
{
    int analog = AnalogRead();
    float voltage = analog * (3.3/1024.0); //0->3.3 => 0->1024

    return voltage;
}