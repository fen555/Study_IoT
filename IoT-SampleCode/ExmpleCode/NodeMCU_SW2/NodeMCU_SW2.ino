#define sw1 D1              // Declare all variables
#define sw2 D2
#define ledPin1 D5
#define ledPin2 D6
int st_sw1 = 0;             // Set inital status
int st_sw2 = 0;
int st_1 = 0;
int st_2 = 0;
int last_st_sw1 = 1;
int last_st_sw2 = 1;
void setup() 
{
  pinMode(ledPin1, OUTPUT); // Set pin mode
  pinMode(ledPin2, OUTPUT);
  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
}
void loop() 
{
  st_sw1 = digitalRead(sw1);                // Read input port1
  if ((st_sw1 == 0) && (last_st_sw1 == 1))  // Check current status
  {
    st_1 = ~st_1;                           // Toggle
    digitalWrite(ledPin1, st_1);            // Drive LED1
    delay(250);
  }
  last_st_sw1 = st_sw1;                     // Update current status

  st_sw2 = digitalRead(sw2);                // Read input port2
  if ((st_sw2 == 1) && (last_st_sw2 == 0))  // Check current status
  {
    st_2 = ~st_2;                           // Toggle
    digitalWrite(ledPin2, st_2);            // Drive LED2
    delay(250);
  }
  last_st_sw2 = st_sw2;                     // Update current status
}

