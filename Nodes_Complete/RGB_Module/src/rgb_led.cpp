//**************************************************
// File: rgb_led.cpp
// Author: Isaac Wittmeier
// Description: Controls the RGB led
//**************************************************
#include <Arduino.h>
#include "pinMaps.h"
#include "rgb_led.h"

//led pins
int red = D1;
int green = D2;
int blue = D3;

//helper function
//display a color on led
void RGB_Color(int redVal, int greenVal, int blueVal)
{
    analogWrite(red, redVal);
    analogWrite(green, greenVal);
    analogWrite(blue, blueVal);
}

//setup rgb led
void RGB_Init()
{
    //set pin modes
    pinMode(red, OUTPUT);
    pinMode(green, OUTPUT);
    pinMode(blue, OUTPUT);

    //start off
    RGB_Change("R000G000B000");
}

//decompose display string and display
//string length must be exactly 12 chars
//ie. "R001G255B125"
//returns bool - success or fail
bool RGB_Change(String value)
{
    //check value length
    if (value.length() != 12) return false;

    //get values from string
    int redVal = value.substring(1,3).toInt();
    //if (redVal < 0 || redVal > 255) return false;
    int greenVal = value.substring(5,7).toInt();
    //if (greenVal < 0 || greenVal > 255) return false;
    int blueVal = value.substring(9,11).toInt();
    //if (blueVal < 0 || blueVal > 255) return false;

    //change color
    RGB_Color(redVal, greenVal, blueVal);
    return true;
}