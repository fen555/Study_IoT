#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

#include <Adafruit_Sensor.h>

char auth[] = "7f965a4a4dc34c8fb4532d5e81d0a3c0"; // CHANGEEEEEEEEEEEEEEEEEEEEEEEE

SimpleTimer timer;

void setup()
{
  Serial.begin(115200);
  
  pinMode(D5,OUTPUT);
  Blynk.begin(auth, "Apple TV", "APPLE_TV"); // CHANGEEEEEEEEEEEEEEEEEEEEEEEE

 
  
  // Setup a function to be called every second
  timer.setInterval(5000L, sendUptime);
}

void sendUptime()
{
  Serial.println("b");
  
  
}

void loop()
{
 
  Blynk.run();
  timer.run();
  
}
