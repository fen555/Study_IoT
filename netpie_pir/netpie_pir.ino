#include <ESP8266WiFi.h>
#include <MicroGear.h>
#define pirPin 4 // Input for HC-SR501 //D2
const char* ssid = "vaseline";
const char* password = "mmm02333";

#define APPID "COFEN"
#define KEY "pjdeqj4XylKD7LI" 
#define SECRET "vTxlt4B4shgvDsvvXBmvM0ieQ"
#define ALIAS "piepir"
WiFiClient client;
int timer = 0;
int pirValue; // variable to store read PIR Value
char str[32];

MicroGear microgear(client);

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
  Serial.print("Incoming message --> ");
  msg[msglen] = '\0';
  Serial.println((char *)msg);
  String msg2 = String((char*)msg);//////////////////////////
  if (msg2 == "ON") {
    //digitalWrite(relayPin, HIGH);
   // digitalWrite(led, HIGH);
   // microgear.chat("testledstatus", "ON");    // led status
  //  microgear.chat("name", "ON");    // led status
  }
  else if (msg2 == "OFF") {
    // digitalWrite(relayPin, LOW);
   // digitalWrite(led, LOW);
   // microgear.chat("testledstatus", "OFF");  // led status
  // microgear.chat("name", "OFF");  // led status
  }/////////////////////////////////////////////////////
}

void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
  Serial.println("Connected to NETPIE...");
  microgear.setAlias(ALIAS);
}
///////////////////////////////////////////////////////////////////////////////////////
void onFoundgear(char *attribute, uint8_t* msg, unsigned int msglen) {
  Serial.print("Found new member --> ");
  for (int i = 0; i < msglen; i++)
    Serial.print((char)msg[i]);
  Serial.println();
}
void onLostgear(char *attribute, uint8_t* msg, unsigned int msglen) {
  Serial.print("Lost member --> ");
  for (int i = 0; i < msglen; i++)
    Serial.print((char)msg[i]);
  Serial.println();
}

/////////////////////////////////////////////////////////////////////////////////////////////
void setup() {

  microgear.on(MESSAGE, onMsghandler);
  microgear.on(CONNECTED, onConnected);
  microgear.on(PRESENT, onFoundgear);
  microgear.on(ABSENT, onLostgear);
  Serial.begin(115200);
  pinMode(pirPin, INPUT);
  Serial.println("Starting...");

  if (WiFi.begin(ssid, password)) {
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  microgear.init(KEY, SECRET, ALIAS);
  microgear.connect(APPID);
}

void loop() {

  pirValue = digitalRead(pirPin);
  Serial.println(pirValue);

  
  if (microgear.connected()) {
    Serial.println("connected");
     microgear.loop();
    if (timer >= 1000) {
      sprintf(str, "%d",pirValue);/////////////////////
      Serial.println(str);
      Serial.println("Sending --> ");
      microgear.publish("/pir", str);////////////////////////////////////datasourseมั้ง
      timer = 0;
    }
    else timer += 100;
  }
  else {
    Serial.println("connection lost, reconnect...");
    if (timer >= 5000) {
      microgear.connect(APPID);
      timer = 0;
    }
    else timer += 100;
  }
  delay(1000);
}

