//**************************************************
// File: i2c_lcd.cpp
// Author: Isaac Wittmeier
// Description: LCD functions
//**************************************************
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

//initialize the lcd
void LCD_Init();

//display a new message
//max 32 chars, cuts of rest
void LCD_Display(String message);