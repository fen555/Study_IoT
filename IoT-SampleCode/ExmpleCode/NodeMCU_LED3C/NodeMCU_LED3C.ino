#define B_pin D0  //Blue
#define G_pin D1  //Green
#define R_pin D2  //Red
int st_B = 0;
int st_G = 0;
int st_R = 0;
void setup()
{
  pinMode(B_pin, OUTPUT); // Set pin as output
  pinMode(G_pin, OUTPUT);
  pinMode(R_pin, OUTPUT);
}
void loop()
{
  displayRGB(0, 0, 0);  // Drive RGB LED with 3-bit data
  delay(2000);          // Delay 2 seconds
  displayRGB(1, 0, 0);
  delay(2000);
  displayRGB(1, 1, 0);
  delay(2000);
  displayRGB(0, 1, 0);
  delay(2000);
  displayRGB(0, 1, 1);
  delay(2000);
  displayRGB(0, 0, 1);
  delay(2000);
  displayRGB(1, 0, 1);
  delay(2000);
  displayRGB(1, 1, 1);
  delay(2000);
}
void displayRGB(int R, int G, int B) 
// Send 3-bit digital data to 3 output pins function
{
  digitalWrite(B_pin, B);
  digitalWrite(G_pin, G);
  digitalWrite(R_pin, R);
}
