#include <ESP8266WiFi.h>                // Include main library
const char* ssid     = "L-Family";      // Set SSID
const char* password = "0818453153";    // Set password
const char* thing = "stLed";            // Thing name is  stLed
const char* host = "dweet.io";
const int pin1 =  D0;
boolean st_1 = false;                    //false//true
void setup() 
{
  Serial.begin(115200);
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);                 // Print SSID
  WiFi.begin(ssid, password);           // Send password
  while (WiFi.status() != WL_CONNECTED) // Check connection
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());       // Print IP address
  pinMode(pin1, OUTPUT);
}
String mag;
void loop() 
{
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;              // Set HTTP port
  if (!client.connect(host, httpPort)) 
  {
    Serial.println("connection failed");
    return;
  }
  // Send URL to dweet.io 
  client.print(String("GET /get/latest/dweet/for/") + thing + (" HTTP/1.1\r\n") +
               "Host: " + host + "\r\n" +
               "Connection: keep-alive\r\n" +
               "Cache-Control: max-age=0\r\n\r\n");
  delay(1000);
  int st_response = -1;               // 200 OK
  int st_check_Mo = -1;               // Last-Modified
  mag = "";
  while (client.available())          // Read button status
  {
    String line = client.readStringUntil('\r');
    Serial.print(line);
    mag = line;
    if (mag.indexOf("Last-Modified") != -1)
      st_check_Mo = 1;
    if (mag.indexOf("200 OK") != -1)
      st_response = 1;
  }
  Serial.println(st_response);       // Print LED-D0 status
  String val_1 = getstring(mag, "LED\":", "}"); //
  Serial.println("val................");
  if (st_response == 1) 
  {
    Serial.println(val_1);
    st_1 = val_1.toInt();
    digitalWrite(pin1, st_1);
  }
  Serial.println("closing connection");
}
String getstring(String data, String str_start, String str_end)
{
  int lastStringLength = data.length();
  int StrLength = str_start.length();
  int stratidex = data.indexOf(str_start);
  String Mag  = data.substring(stratidex + StrLength, lastStringLength);
  int endindex = -1;
  if (Mag.indexOf(str_end) != -1)
    endindex = Mag.indexOf(str_end);

  Mag  = Mag.substring(0, endindex);
  if (Mag == "")
    Mag = "-1";
  return Mag;
}

