#define sw1 D1          // Declare variables
#define SSR1 D3
int st_sw1 = 0;
int st_1 = 0;
int last_st_sw1 = 0;    // Set current state
void setup()
{
  pinMode(SSR1, OUTPUT);
  pinMode(sw1, INPUT);
}

void loop()
{
  st_sw1 = digitalRead(sw1); // Read the input switch status
  if ((st_sw1 == 0) && (last_st_sw1 == 1))  // Check switch pressed
  {
    st_1 = ~st_1;               // Toggle
    digitalWrite(SSR1, st_1);   // Activate Solid-state relay
    delay(250);                 // Short delay
  }
  last_st_sw1 = st_sw1;         // Keep the current status of switch
}
