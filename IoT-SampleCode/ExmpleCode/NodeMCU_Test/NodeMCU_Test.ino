const int PIN_LED = D0; // On-board LED is connected to D0 or GPIO16
void setup() 
{
  pinMode(PIN_LED, OUTPUT);
}
void loop() 
{
    digitalWrite( PIN_LED, HIGH );
    delay(1000);
    digitalWrite( PIN_LED, LOW );
    delay(1000);
}
