#include <stdio.h>      // include file stdio.h for function sprintf()
#define ANALOG_PIN A0   // Analog input at pin An 0.
int analogValue = 0;    // variable to store analog value

void setup()
{
  Serial.begin(115200);   // set serial port at 9600 bps
}

void loop()
{
  char str[5];                            // Declare string variable
  int temp;                               // Temporary variable.
  analogValue = analogRead(ANALOG_PIN);   // Read analog input at pin An 0.
  temp = analogValue * 3.3 / 1023 * 1000; // convert to volt and scale *1000
  sprintf(str, "%4d", temp);              // convert interger to string
  Serial.print("Analog input0 = ");       // print string
  Serial.print(str[0]);                   // print voltage in first digit
  Serial.print(".");
  if (str[1] == ' ') Serial.print("0");
  else  Serial.print(str[1]);             // print voltage in 3rd digit (0.1 volt)
  if (str[2] == ' ') Serial.print("0");
  else  Serial.print(str[2]);             // print voltage in 4th digit (0.01 volt)
  Serial.print(str[3]);                   // print voltage in 5th digit (0.001 volt)
  Serial.println(" Volt");
  delay(200);                             // wait 0.2 second
}
