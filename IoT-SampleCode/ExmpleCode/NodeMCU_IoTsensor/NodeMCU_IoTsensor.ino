#include "DHT.h"                          // Include DHT sensor library
#include <ESP8266WiFi.h>                  // Include main library
const char* ssid     = "L-Family";        // Set SSID
const char* password = "0818453153";      // Set password
const char* thing =  "NodeMCU_IoTsensor"; // Set Thing name
const char* host = "dweet.io";            // Set Host

#define DHTPIN  D4                        // Define DHT sensor pin
#define DHTTYPE DHT11                     // Define DHT sensor type
#define trigPin D5                        // Define HC-SR04 Trig pin
#define echoPin D6                        // Define HC-SR04 Echo pin

DHT dht(DHTPIN, DHTTYPE, 15);             // Initial DHT sensor
void setup() 
{
  Serial.begin(115200);                   // Set baudrate
  delay(10);
  pinMode(trigPin, OUTPUT);               // Set pin mode for HC-SR04 
  pinMode(echoPin, INPUT);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);                   // Print SSID
  WiFi.begin(ssid, password);             // Send password
  while (WiFi.status() != WL_CONNECTED)   // Check connecting status
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());         // Print IP address
  dht.begin();
}
int count = 0;                            // Set default value
int sensorValue = 0;
float Humidity = 0;
float Temp = 0;
long distance;
long dis_val;
void loop() 
{
  sensorValue = analogRead(A0);           // Read A0 input
  float h = dht.readHumidity();           // Read Humidity from DHT sensor
  float t = dht.readTemperature();        // Read Temperature from DHT sensor
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f))   // Check sum of DHT sensor
  {
    Serial.println("Failed to read from DHT sensor!"); // Print error
  }
  else 
  {
    Humidity = h;                         // Store DHT data to variable
    Temp = t;
  }
  delay(1000);

  distance = read_sr_04();                // Read HC-SR04 
  if (distance <= 200 && distance >= 0)   // Check data range
  {
    dis_val = distance ;                  // Store HC-SR04 data to variable
  }
  delay(1000);

  ++count;                                // Count value
  delay(1000);

  WiFiClient client;
  const int httpPort = 80;                // Set HTTP port
  if (!client.connect(host, httpPort))    // Check network connection 
  {
    Serial.println("connection failed");
    return;
  }
  // Send URL to dweet.io
  String url =  String("/dweet/for/") + thing + "?";
  url += "Count=";
  url += count;
  url += "&Analog=";
  url += sensorValue;
  url += "&Humidity=";
  url += Humidity;
  url += "&Temperature=";
  url += Temp;
  url += "&Distance=";
  url += dis_val;

  // Print broker data
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: keep-alive\r\n" +
               "Cache-Control: max-age=0\r\n\r\n");
  delay(3000);
  while (client.available()) 
  {
    String line = client.readStringUntil('\r');
    Serial.println(line);             // Print response status 
  }
}

long  read_sr_04()                    // HC-SR04 reading function
{
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;   // Return data with cm. unit
  return  distance;
}

