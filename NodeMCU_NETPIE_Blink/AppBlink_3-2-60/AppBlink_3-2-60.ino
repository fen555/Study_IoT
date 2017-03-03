#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN            12    
#define DHTTYPE           DHT22

DHT_Unified dht(DHTPIN, DHTTYPE);

char auth[] = "d8a07025c5e3496e84bae6aa9b7e9091"; // CHANGEEEEEEEEEEEEEEEEEEEEEEEE

SimpleTimer timer;

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, "Apple TV", "APPLE_TV"); // CHANGEEEEEEEEEEEEEEEEEEEEEEEE

  dht.begin();
  
  // Setup a function to be called every second
  timer.setInterval(5000L, sendUptime);
}

void sendUptime()
{
  Blynk.virtualWrite(V5, millis() / 1000);
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  if (!isnan(event.temperature)) {
    Blynk.virtualWrite(V1, event.temperature);
    Serial.print(event.temperature);//
    Serial.print("\t");
  }
  dht.humidity().getEvent(&event);
  if (!isnan(event.relative_humidity)) {
    Blynk.virtualWrite(V2, event.relative_humidity);
    Serial.println(event.relative_humidity);
  }
  
}

void loop()
{
  Blynk.run();
  timer.run();
}
