const int PIN_LED = D4; // Communication status LED pin as D4 or GPIO2
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
