#define B_pin D0  //Blue
#define G_pin D1  //Green
#define R_pin D2  //Red
int st_R = 255;
int st_G = 0;
int st_B = 0;

void setup()
{
  pinMode(B_pin, OUTPUT); // Set pin as output
  pinMode(G_pin, OUTPUT);
  pinMode(R_pin, OUTPUT);
}
void loop() 
{
  for (int i = 0; i < 256; i++)   // Set loop
  {
    st_B = 0;                     // Clear BLUE data
    st_G++;                       // Increase GREEN data
    displayRGB(st_R, st_G, st_B); // Drive LED with PWM
    delay(30);                    // Short delay
  }
  for (int i = 0; i < 256; i++) 
  {
    st_R--;                       // Decrease RED data
    displayRGB(st_R, st_G, st_B); // Drive LED with PWM
    delay(30);                    // Short delay
  }
  for (int i = 0; i < 256; i++) 
  {
    st_R = 0;                     // Clear RED data
    st_B++;                       // Increase BLUE data
    displayRGB(st_R, st_G, st_B); // Drive LED with PWM
    delay(30);                    // Short delay
  }
  for (int i = 0; i < 256; i++) 
  {
    st_G--;                       // Decrease GREEN data
    displayRGB(st_R, st_G, st_B); // Drive LED with PWM
    delay(30);                    // Short delay
  }
  for (int i = 0; i < 256; i++) 
  {
    st_G = 0;                     // Clear GREEN data
    st_R++;                       // Increase RED data
    displayRGB(st_R, st_G, st_B); // Drive LED with PWM
    delay(30);                    // Short delay
  }
  for (int i = 0; i < 256; i++) 
  {
    st_B--;                       // Decrease BLUE data
    displayRGB(st_R, st_G, st_B); // Drive LED with PWM
    delay(30);                    // Short delay
  }
}
void displayRGB(int R, int G, int B) 
// Drive LED with PWM by using analogWrite function
{
  analogWrite(B_pin, B);
  analogWrite(G_pin, G);
  analogWrite(R_pin, R);
}

