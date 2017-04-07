#include <ESP8266WiFi.h>                // Include main library
const char* ssid     = "Your SSID";     // Set SSID
const char* password = "Your password"; // Set password
const char* host = "dweet.io";          // Set host 

void setup() 
{
  Serial.begin(115200);                 // Print setting message
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");                  // Print WiFi status
  }
  Serial.println("");
  Serial.println("WiFi connected");     // Print connect status
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());       // Print IP address
}

void loop() 
{
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;              // Set HTTP Port
  if (!client.connect(host, httpPort))  // Test connection
  {
    Serial.println("connection failed");  // Print connection fail messag
    return;
  }
  //https://dweet.io/get/latest/dweet/for/Test01
  client.print(String("GET /get/latest/dweet/for/Test01 HTTP/1.1\r\n") +
               "Host: " + host + "\r\n" +
               "Connection: keep-alive\r\n" +
               "Cache-Control: max-age=0\r\n\r\n");
  delay(3000);
  while (client.available()) 
  {
    String line = client.readStringUntil('\r');
    Serial.println(line);
  }
}
