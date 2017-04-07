#include <Wire.h>               // Include I2C library 
#include <LiquidCrystal_I2C.h>  // Include LCD-I2C library 
// Set the LCD address to 0x27/0X3F for I2C-LCD16x2 module
LiquidCrystal_I2C lcd(0x3F, 16, 2); 
int BH1750address = 0x23;       // Set BH1750 address
byte buff[2];
void setup() 
{
  Wire.begin();
  lcd.begin();                  // Initialize the LCD
  lcd.backlight();              // Turn on the blacklight   
  lcd.setCursor(0, 0);
  lcd.print("Read BH1750");     // Print a message.
  lcd.setCursor(0, 1);  
  lcd.print("Light= ");         // Print parameter name
}

void loop() 
{
  uint16_t val = 0;
  BH1750_Init(BH1750address);             // Initial BH1750
  delay(200);
  if (2 == BH1750_Read(BH1750address))    // Read and check data from BH1750
  {
    val = ((buff[0] << 8) | buff[1])/1.2;
    lcd.setCursor(7, 1);
    lcd.print(val + String(" lux    "));  // Show light density unit
  }
  delay(150);
}
int BH1750_Read(int address)              // BH1750 read data function
{
  int i = 0;
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);
  while (Wire.available())
  {
    buff[i] = Wire.read();                // Read one byte
    i++;
  }
  Wire.endTransmission();
  return i;
}
void BH1750_Init(int address)             // BH1750 initial function
{
  Wire.beginTransmission(address);
  Wire.write(0x10);                       // Start operation
  Wire.endTransmission();
}

