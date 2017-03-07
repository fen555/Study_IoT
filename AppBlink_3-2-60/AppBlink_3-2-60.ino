#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN            2    
#define DHTTYPE           DHT22
const char* ssid = "vaseline";
const char* password = "mmm02333";

DHT_Unified dht(DHTPIN, DHTTYPE);
DHT dht2(DHTPIN, DHTTYPE, 15);

static const char* host = "api.thingspeak.com";
static const char* apiKey = "XXXJJI2NYIA5DA14";  
const int updateThingSpeakInterval = 15 * 1000;

char auth[] = "d8a07025c5e3496e84bae6aa9b7e9091"; // CHANGEEEEEEEEEEEEEEEEEEEEEEEE

SimpleTimer timer;


void setup()
{
  Serial.begin(115200);
   dht.begin();
  

Blynk.begin(auth, "vaseline", "mmm02333"); // CHANGEEEEEEEEEEEEEEEEEEEEEEEE

 
  
  // Setup a function to be called every second
  timer.setInterval(5000L, sendUptime);
}

void sendUptime()
{
  Serial.println("b");
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
  //Serial.println("a");
  float h = dht2.readHumidity();
  float t = dht2.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Fail");
    return;
  }
  Serial.print(h);
  Serial.print(" % \t");
  Serial.println(t);//พิมพ์ค่าอุณหภูมิ

  //delay(3000);

   // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        DEBUG_PRINTLN("connection failed");
        return;
    }

    // We now create a URI for the request
    String url = "/update/";
    url += "?key=";
    url += apiKey;
    url += "&field1=";
    url += t;
    url += "&field2=";
    url += h;
    url += "&field3=";
    url += (t - ((100-h)/5));
    

    DEBUG_PRINT("Requesting URL: ");
    DEBUG_PRINTLN(url);
    Serial.println(url);
    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
  Blynk.run();
  timer.run();
  
}
