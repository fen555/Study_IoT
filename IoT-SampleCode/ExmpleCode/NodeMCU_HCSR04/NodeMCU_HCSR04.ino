#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27/0X3F for I2C-LCD16x2 module
LiquidCrystal_I2C lcd(0x3F, 16, 2);
long distance = 0;
#define trigPin D5
#define echoPin D6
void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.begin();                    // initialize the LCD
  lcd.backlight();                // Turn on LED backlight
  lcd.setCursor(0, 0);
  lcd.print("HC-SR04 Reading");   // Print some message
  lcd.setCursor(0, 1);
  lcd.print("Distance = ");
}

void loop()
{
  distance = read_hc_sr04();              // Read data from HC-SR04
  if (distance <= 200 && distance >= 0)   // Set distance display range
  {
    lcd.setCursor(11, 1);
    lcd.print(distance + String("cm  ")); // Print distance value
    delay(10);
  }
}
long  read_hc_sr04()                      // Read the distance value for HC-SR04 
{
  long duration, distance;
  digitalWrite(trigPin, LOW);             // Trig signal sending
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);      // Echo signal receiving
  distance = (duration / 2) / 29.1;       // Calculate the distance result
  return  distance;                       // Return value
}

