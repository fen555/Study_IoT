int pinTone = D7;
void setup()
{
  analogWrite(pinTone,255);
  delay(1000);
}
void loop() 
{
  analogWriteFreq(440);
  delay(500);
  analogWriteFreq(587);
  delay(500);
}

