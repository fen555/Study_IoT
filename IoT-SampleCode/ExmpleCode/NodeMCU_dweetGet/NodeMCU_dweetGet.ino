#include <ESP8266WiFi.h>              // Include main library
const char* ssid     = "Your SSID";    // Set your SSID
const char* password = "Your password";  // Set your password
const char* thing = "NodeMCU_Send";   // Set Thing name
const char* host = "dweet.io";        // Set host 
int count = 0;
int sensorValue = 0;
void setup() 
{
  Serial.begin(115200);               // Print setting message
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");                // Print WiFi status
  }
  Serial.println("");
  Serial.println("WiFi connected");   // Print connect status
  Serial.println("IP address: ");     
  Serial.println(WiFi.localIP());     // Print IP address
}
void loop() 
{
  sensorValue = analogRead(A0);       // Read analog input
  delay(1000);
  ++count;                            // Count value
  WiFiClient client;
  const int httpPort = 80;            // Set HTTP port
  if (!client.connect(host, httpPort))// Test connection 
  {
    Serial.println("connection failed"); // Print connection fail message
    return;
  }
  String url =  String("/dweet/for/") + thing + "?"; // Set message
  url += "count=";
  url += count;
  url += "&Analog=";
  url += sensorValue;
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: keep-alive\r\n" +
               "Cache-Control: max-age=0\r\n\r\n");
  Serial.println("URL : ");         
  Serial.println(url);              // Print URL 
  delay(3000);
  
  while (client.available()) 
  {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  Serial.println("closing connection"); // Print closing status
}

