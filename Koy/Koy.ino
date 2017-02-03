#include "DHT.h"
#include <LiquidCrystal.h>
#define DHTPIN 9
DHT dht(DHTPIN, DHT22, 15);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // put your setup code here, to run once:
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2); // จอกว้าง 16 ตัวอักษร 2 บรรทัด
  lcd.print("LCDisplay"); // แสดงผลคำว่า Hello, world! ออกหน้าจอ
  lcd.setCursor(0, 1); // เลื่อนเคเซอร์ไปบรรทัดที่ 2 ลำดับที่ 0 (ก่อนหน้าตัวอักษรแรก)
  lcd.print("by CF"); 
  delay(3000); // หน่วงเวลา 3 วินาที
  lcd.clear(); // ล้างหน้าจอ

}

void loop() {


  digitalWrite(7,HIGH);
  digitalWrite(8,LOW);
  delay(1000);
  digitalWrite(8,HIGH);
  digitalWrite(7,LOW);
  delay(1000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if(isnan(h) || isnan(t)){
   //  if( isnan(t)){
    Serial.println("Fail");
    return;
    }
    Serial.print("T = ");
    Serial.println(t);
    Serial.print("H = ");
    Serial.println(h);

    lcd.setCursor(0, 0);
    lcd.print("T = ");
    lcd.print(t);
    lcd.setCursor(0, 1);
    lcd.print("H = ");
    lcd.print(h);
    delay(500); // หน่วงเวลา 0.5 วินาที
    lcd.clear(); // ล้างหน้าจอ
    delay(500); // หน่วงเวลา 0.5 วินาที
    
  // put your main code here, to run repeatedly:

}
