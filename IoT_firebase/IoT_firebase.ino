#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <DHT.h>
// Config Firebase
#define FIREBASE_HOST "testiot-3b654.firebaseio.com"
#define FIREBASE_AUTH "HCtLkChc1xouVRFenlhrAxGJuVcRpBnzx0YxL9hw"
// Config connect WiFi
#define WIFI_SSID "Apple TV"
#define WIFI_PASSWORD "APPLE_TV"
// Config DHT
#define DHTPIN D4
#define DHTTYPE DHT22
String name;
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
// connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  dht.begin();
}
void loop() {
// Read temp & Humidity for DHT22
float h = dht.readHumidity();
float t = dht.readTemperature();
if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
delay(500);
return;
  }
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["temperature"] = t;
  root["humidity"] = h;
// append a new value to /logDHT
  String name = Firebase.push("logDHT", root);
// handle error
if (Firebase.failed()) {
      Serial.print("pushing /logDHT failed:");
      Serial.println(Firebase.error());  
return;
  }
  Serial.print("pushed: /logDHT/");
  Serial.println(name);
delay(5000);
}
