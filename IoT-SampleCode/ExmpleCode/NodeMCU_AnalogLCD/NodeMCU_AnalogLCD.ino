#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);
void setup()
{
  lcd.begin();                // initialize the LCD  
  lcd.backlight();            // Turn on the blacklight 
  lcd.setCursor(0, 0);
  lcd.print("Read Analog");   // Print a message on line 1
  lcd.setCursor(0, 1);        
  lcd.print("Analog(A0)=");   // Print message on line 2
}

void loop()
{
  lcd.setCursor(11, 1);
  lcd.print(analogRead(A0) + String("        ")); // Print analog value
  delay(100);  
}
