#define ANALOG_PIN A0       // Analog input at pin A0.
int analogValue = 0;        // Variable for store analog value

void setup()
{
  Serial.begin(115200);       // set serial port at 115200 bps
}

void loop()
{
  analogValue = analogRead(ANALOG_PIN);   // Read analog input at pin An 0.
  Serial.print("Analog input0 = ");       // Send string to serial port.
  Serial.println(analogValue);            // Send analog value to serial port.
  delay(300);                            // Delay 0.3 second.
}
