/*  NETPIE ESP8266 basic sample                            */
/*  More information visit : https://netpie.io             */

#include <ESP8266WiFi.h>
#include <MicroGear.h>

const char* ssid     = "vaseline";
const char* password = "mmm02333";

#define APPID   "COFEN"                   //
#define KEY     "pjdeqj4XylKD7LI"              //
#define SECRET  "vTxlt4B4shgvDsvvXBmvM0ieQ"   //
#define ALIAS   "esp8266"

WiFiClient client;

int led = D1;

int timer = 0;
MicroGear microgear(client);
/* If a new message arrives, do this */
void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
    Serial.print("Incoming message --> ");
    msg[msglen] = '\0';
    Serial.println((char *)msg);
    String msg2 = String((char*)msg);

    if (msg2 == "ON") {
      //digitalWrite(relayPin, HIGH);
      digitalWrite(led, HIGH);
      microgear.chat("testledstatus", "ON");    // led status
    }
    else if (msg2 == "OFF") {
     // digitalWrite(relayPin, LOW);
      digitalWrite(led, LOW);
      microgear.chat("testledstatus", "OFF");  // led status
    }
}

void onFoundgear(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.print("Found new member --> ");
    for (int i=0; i<msglen; i++)
        Serial.print((char)msg[i]);
    Serial.println();  
}

void onLostgear(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.print("Lost member --> ");
    for (int i=0; i<msglen; i++)
        Serial.print((char)msg[i]);
    Serial.println();
}
/* When a microgear is connected, do this */
void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.println("Connected to NETPIE...");
    microgear.setAlias(ALIAS);
}


void setup() {

    pinMode(led, OUTPUT);
    
    microgear.on(MESSAGE,onMsghandler);
    microgear.on(PRESENT,onFoundgear);
    microgear.on(ABSENT,onLostgear);
    microgear.on(CONNECTED,onConnected);

    Serial.begin(115200);
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

    microgear.init(KEY,SECRET,ALIAS);
    microgear.connect(APPID);
}

void loop() {
    if (microgear.connected()) {
        Serial.println("connected");
        microgear.loop();
    
        if (timer >= 1000) {
            Serial.println("Publish...");
            //microgear.chat(ALIAS,"Hello ^^");
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
    delay(100);
}
