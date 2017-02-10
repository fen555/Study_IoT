#include <ESP8266WiFi.h>
#include <DHT.h>
#define DHTPIN D1
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE, 15);
#define ledPin1 D4
const char* ssid = "Apple TV";
const char* password = "APPLE_TV";
static const char* host = "api.thingspeak.com";
static const char* apiKey = "XXXJJI2NYIA5DA14";
const int updateThingSpeakInterval = 15 * 1000;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("DHT Test");
  dht.begin();
  delay(10);
  pinMode(ledPin1, OUTPUT);

  Serial.println();
  Serial.print("Connect to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  digitalWrite(ledPin1, HIGH);
  Serial.println("");
  Serial.println("Connected");
  Serial.print("IP : ");
  Serial.println(WiFi.localIP());
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();
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

    DEBUG_PRINT("Requesting URL: ");
    DEBUG_PRINTLN(url);
    Serial.println(url);
    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");

}
