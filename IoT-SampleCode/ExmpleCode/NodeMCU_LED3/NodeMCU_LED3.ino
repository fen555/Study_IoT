#define ledPin1 D1    // Define pin name
#define ledPin2 D2
#define ledPin3 D3
void setup() 
{
  pinMode(ledPin1, OUTPUT); // Set D1 pin as output
  pinMode(ledPin2, OUTPUT); // Set D2 pin as output
  pinMode(ledPin3, OUTPUT); // Set D3 pin as output
}

void loop() 
{
  digitalWrite(ledPin1, 0); // Set display pattern off-off-on 
  digitalWrite(ledPin2, 0);
  digitalWrite(ledPin3, 1);
  delay(1000);              // Delay 1 second
  digitalWrite(ledPin1, 0); // Set display pattern off-on-on
  digitalWrite(ledPin2, 1);
  digitalWrite(ledPin3, 1);
  delay(1000);              // Delay 1 second
  digitalWrite(ledPin1, 1); // Set display pattern on-on-on
  digitalWrite(ledPin2, 1);
  digitalWrite(ledPin3, 1);
  delay(1000);              // Delay 1 second
  digitalWrite(ledPin1, 0); // Turn off all
  digitalWrite(ledPin2, 0);
  digitalWrite(ledPin3, 0);
  delay(1000);              // Delay 1 second
}

