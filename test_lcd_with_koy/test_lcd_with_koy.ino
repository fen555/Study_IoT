#include <LiquidCrystal.h>
#include <DHT.h>
LiquidCrystal lcd(12, 14, 2, 0, 4, 5);
#define DHTPIN D7
DHT dht(DHTPIN, DHT22, 15);
void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.setCursor(2, 0);
  lcd.print("Love Monster");
  dht.begin();
}
void loop() {
  lcd.clear();
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  lcd.setCursor(2, 0);
  lcd.print("T = ");
  lcd.setCursor(6, 0);
  lcd.print(t);
  lcd.setCursor(2, 1);
  lcd.print("H = ");
  lcd.setCursor(6, 1);
  lcd.print(h);
  delay(2000);
}

