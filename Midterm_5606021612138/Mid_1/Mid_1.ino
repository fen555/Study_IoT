//ต่ำกว่า 30 ไฟติด 1 ดวง 30-35 ไฟติด 2 ดวง มากกว่านั้นติด 3 ดวง
#include "DHT.h"
#define DHTPIN 9
DHT dht(DHTPIN, DHT22, 15);


void setup() {

  pinMode(4, OUTPUT);
  Serial.begin(9600);
  digitalWrite(4, LOW);
  dht.begin();

}

void loop() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  digitalWrite(4, LOW);
  if (isnan(h) || isnan(t)) {
    Serial.println("Fail");
    return;
  }
  Serial.print(h);
  Serial.print(" % \t");
  Serial.println(t);//พิมพ์ค่าอุณหภูมิ
  
  if (t > 35) {
    Serial.println("s");
    digitalWrite(4, HIGH);

  }
  

  delay(1000);
}

