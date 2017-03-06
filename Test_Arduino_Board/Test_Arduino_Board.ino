//ต่ำกว่า 30 ไฟติด 1 ดวง 30-35 ไฟติด 2 ดวง มากกว่านั้นติด 3 ดวง
#include "DHT.h"
#define DHTPIN 9
DHT dht(DHTPIN, DHT22, 15);


void setup() {

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
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
  
  if (t < 30) {
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  }
  else if (t >= 30 && t<35) {
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
  }
  else if (t >= 35) {
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
  }
  else {
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
  }

  delay(1000);
}

