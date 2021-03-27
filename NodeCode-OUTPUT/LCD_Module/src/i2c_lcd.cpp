//**************************************************
// File: i2c_lcd.cpp
// Author: Isaac Wittmeier
// Description: LCD functions
//**************************************************
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

LiquidCrystal_I2C lcd(0x27, 16,2);  //i2c addr, 16 chars, 2 line display

//initialize the lcd
void LCD_Init()
{
    lcd.init(); //start lcd
    lcd.setBacklight(70); //turn on backlight
}

//display a new message
//max 32 chars
void LCD_Display(String message)
{
    char buff[57] = {0}; 

    //make sure message long enough
    while (message.length() < 32) message += " ";

    //overlap past lcd edge is 23 chars
    //padding isrequired to fill this unseen space
    for (int i = 0; i < 56; i++)
    {   
        if (i < 16) buff[i] = message[i];
        else if (i > 39) buff[i] = message[i-24];
        else buff[i] = ' ';
        Serial.print(buff[i]);
    }

    //display new message
    lcd.clear();
    lcd.print(buff);
}