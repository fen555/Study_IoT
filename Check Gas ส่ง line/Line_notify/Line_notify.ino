void Line_Notify(String message) ;

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Config connect WiFi
#define WIFI_SSID "vaseline" // แก้ชื่อ ssid
#define WIFI_PASSWORD "mmm02333" // แก้รหัสผ่าน

#define mqtt_server "m12.cloudmqtt.com"
#define mqtt_port 10250
#define mqtt_user "wvottqye"
#define mqtt_password "tr8fy-KkiXay"
float oldTemp = 0.0;
int v = 0;
WiFiClient espClient;
PubSubClient client(espClient);

// Line config
#define LINE_TOKEN "OzOsSaIKUU1jE1cIQp5vuzYL73jQraU1w7AxKXQFZhU" // แก้ LINE TOKEN
String message = "Hello NodeMCU and Line";
String message2 = "%E0%B8%A1%E0%B8%B5%E0%B8%84%E0%B8%99%E0%B9%80%E0%B8%82%E0%B9%89%E0%B8%B2%E0%B8%A1%E0%B8%B2%E0%B8%A1%E0%B8%B5%E0%B8%84%E0%B8%99%E0%B9%80%E0%B8%82%E0%B9%89%E0%B8%B2%E0%B8%A1%E0%B8%B2";
//Line Notify ยังไม่รองรับภาษาไทย ดังนั้นเราสามารถแปลงข้อความเป็น utf-8 เพื่อส่งเป็นภาษาไทยได้ จาก http://meyerweb.com/eric/tools/dencoder/



void setup() {
 Serial.begin(115200);
pinMode(D1, INPUT);
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
 client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("iotsub", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      client.subscribe("/checkGas");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
      return;
    }
  }
  client.loop();
  
  
 Serial.println("Enter !");
 Serial.println(v);
  //message = value;
 if(v == 1){
  Line_Notify("Check Gas");
 }
 
 //Line_Notify("Distance = " + value);

 Serial.println();
 delay(500);
}

void callback(char* topic, byte* payload, unsigned int length) {
  //Serial.print("Message arrived [");
  //Serial.print(topic);
  String msg = "";
  String to = "";
  int i = 0;
  while (i < length) msg += (char)payload[i++];
//  Serial.println(msg);
  to = topic;
//  Serial.print(to);
  if (to == "/checkGas") {
    Serial.println(msg);
    if (msg.toFloat() > 5) {
      v = 1;
    } else {
      v = 0;
    }
  } 
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
 Serial.println(req);
 client.print(req);
 delay(20);

Serial.println("-------------");
 while (client.connected()) {
 String line = client.readStringUntil('\n');
 if (line == "\r") {
 break;
 }
 Serial.println(line);
 }
 Serial.println("-------------");
}
