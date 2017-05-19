void Line_Notify(String message) ;

#include <ESP8266WiFi.h>

// Config connect WiFi
#define WIFI_SSID "Apple TV" // แก้ชื่อ ssid
#define WIFI_PASSWORD "APPLE_TV" // แก้รหัสผ่าน

// Line config
#define LINE_TOKEN "OzOsSaIKUU1jE1cIQp5vuzYL73jQraU1w7AxKXQFZhU" // แก้ LINE TOKEN
String message = "Hello NodeMCU and Line";
String message2 = "%E0%B8%A1%E0%B8%B5%E0%B8%84%E0%B8%99%E0%B9%80%E0%B8%82%E0%B9%89%E0%B8%B2%E0%B8%A1%E0%B8%B2";
//Line Notify ยังไม่รองรับภาษาไทย ดังนั้นเราสามารถแปลงข้อความเป็น utf-8 เพื่อส่งเป็นภาษาไทยได้ จาก http://meyerweb.com/eric/tools/dencoder/

void setup() {
 Serial.begin(115200);
pinMode(D2, INPUT);
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
}

void loop() {
  int value= digitalRead(D2);
 Serial.println("Enter !");
 Serial.println(value);
 //message = value;
 if(value == 1){
  Line_Notify(message2);
 }
 
 //Line_Notify("Distance = " + value);

 Serial.println();
 delay(2000);
}

void Line_Notify(String message) {
 WiFiClientSecure client;

if (!client.connect("notify-api.line.me", 443)) {
 Serial.println("connection failed");
 return;
 }

String req = "";
 req += "POST /api/notify HTTP/1.1\r\n";
 req += "Host: notify-api.line.me\r\n";
 req += "Authorization: Bearer " + String(LINE_TOKEN) + "\r\n";
 req += "Cache-Control: no-cache\r\n";
 req += "User-Agent: ESP8266\r\n";
 req += "Content-Type: application/x-www-form-urlencoded\r\n";
 req += "Content-Length: " + String(String("message=" + message).length()) + "\r\n";
 req += "\r\n";
 req += "message=" + message;
// Serial.println(req);
 client.print(req);
 delay(20);

 while (client.connected()) {
 String line = client.readStringUntil('\n');
 if (line == "\r") {
 break;
 }
// Serial.println(line);
 }
 Serial.println("-------------");
}
