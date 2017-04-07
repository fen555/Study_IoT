#include <DHT.h>                // Include DHT sensor library
#include <Wire.h>               // Include I2C bus library
#include <LiquidCrystal_I2C.h>  // Include LCD-I2C bus library
#define DHTTYPE DHT11           // Define type of sensor 
#define DHTPIN  D4              // Define connected pin

// Set the LCD address to 0x27/0X3F for I2C-LCD16x2 module
LiquidCrystal_I2C lcd(0x3F, 16, 2); 
 
DHT dht(DHTPIN, DHTTYPE, 15);   // Initial DHT sensor

void setup() 
{
  dht.begin();                  // Start DHT sensor operation
  lcd.begin();                  // Start LCD operation
  lcd.backlight();              // Turn on backlight of LCD
  lcd.setCursor(0, 0);          // Set LCD home position
  lcd.print("Humidity=");       // Print Humidity message
  lcd.setCursor(0, 1);          // Set LCD home position of 2nd line
  lcd.print("Temp=");           // Print Temperature message
}
void loop() 
{
  float humid = dht.readHumidity();     // Read humidity data
  float temp = dht.readTemperature();   // Read temperature data
  lcd.setCursor(10, 0);          
  lcd.print(humid + String("%"));       // Show humidity value in %RH
  lcd.setCursor(6, 1);            
  lcd.print(temp + String("C"));        // Show temperature value in Celcuis
  delay(1000);                          // Delay 1 second before restart
}


