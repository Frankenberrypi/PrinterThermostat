//DFRobot.com
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

int backlightPin = 13;

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  pinMode(backlightPin, INPUT);
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  //lcd.backlight();
  lcd.noBacklight();
  lcd.print("Hello, world!");
  lcd.setCursor(0,1);
  lcd.print("55C");
}

void loop()
{
  if(digitalRead(backlightPin) == HIGH){lcd.backlight();}
    else{lcd.noBacklight();}
}
