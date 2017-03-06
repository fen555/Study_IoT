#include "DHT.h"
#define DHTPIN 9
DHT dht(DHTPIN, DHT22, 15);


void setup() {

  pinMode(8, OUTPUT);
//  pinMode(2, OUTPUT);
//  pinMode(3, OUTPUT);
  Serial.begin(9600);
  dht.begin();

}

void loop() {

//  digitalWrite(8, HIGH);
//  delay(1000);
//  digitalWrite(8, LOW);
//  delay(1000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Fail");
    return;
  }
  Serial.print(h);
  Serial.print(" % \t");
  Serial.println(t);//พิมพ์ค่าอุณหภูมิ

  if (t >= 32) {
    digitalWrite(8, HIGH);
//    digitalWrite(2, HIGH);
//    digitalWrite(3, HIGH);
  }
  else {
    digitalWrite(8, LOW);
//    digitalWrite(2, LOW);
//    digitalWrite(3, LOW);
  }

  delay(1000);
}

