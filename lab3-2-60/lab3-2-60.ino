#include <ESP8266WiFi.h>
#include <DHT.h>
#define DHTPIN D1
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE, 15);
#define ledPin1 D4
const char* ssid = "Apple TV";
const char* password = "APPLE_TV";
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
//  float h = dht.readHumidity();
//  float t = dht.readTemperature();
//  if (isnan(h) || isnan(t)) {
//    Serial.println("Fail");
//    return;
//  }
//  Serial.print(h);
//  Serial.print(" % \t");
//  Serial.println(t);//พิมพ์ค่าอุณหภูมิ
//  if (t >= 40) {
//    digitalWrite(ledPin1, HIGH);
//
//  }
//  else {
//    digitalWrite(ledPin1, LOW);
//
//  }

}
