/*  NETPIE ESP8266 blink                                   */

#include <ESP8266WiFi.h>
#include <MicroGear.h>

const char* ssid     = "Apple TV"; //your ssid
const char* password = "APPLE_TV"; //your password

#define APPID   "COFEN" //your AppID
#define KEY     "pjdeqj4XylKD7LI" //your Key (Device Key)
#define SECRET  "vTxlt4B4shgvDsvvXBmvM0ieQ" //your Secret
#define ALIAS   "TestSwitch"

WiFiClient client;

int timer = 0;
MicroGear microgear(client);

/* If a new message arrives, do this */
void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
    Serial.print("Incoming message --> ");
    msg[msglen] = '\0';
    Serial.println((char *)msg);
// If messaage = 1 On LED, If 0 LED off
    if(*(char *)msg == '1'){ 
        digitalWrite(D1, LOW); // LED on 
        microgear.chat("switch","1");
      }else{ 
        digitalWrite(D1, HIGH); // LED off
        microgear.chat("switch","0");
    }
}

/* When a microgear is connected, do this */
void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.println("Connected to NETPIE...");
    /* Set the alias of this microgear ALIAS */
    microgear.setAlias(ALIAS);
}


void setup() {
    /* Add Event listeners */
    
    /* Call onMsghandler() when new message arraives */
    microgear.on(MESSAGE,onMsghandler);

    /* Call onConnected() when NETPIE connection is established */
    microgear.on(CONNECTED,onConnected);

    Serial.begin(115200);
    Serial.println("Starting...");

    pinMode(D1, OUTPUT); //Set LED Built-in to Output

    /* Initial WIFI, this is just a basic method to configure WIFI on ESP8266.                       */
    /* You may want to use other method that is more complicated, but provide better user experience */
    if (WiFi.begin(ssid, password)) {
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
    }

    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    /* Initial with KEY, SECRET and also set the ALIAS here */
    microgear.init(KEY,SECRET,ALIAS);

    /* connect to NETPIE to a specific APPID */
    microgear.connect(APPID);
}

void loop() {
    /* To check if the microgear is still connected */
    if (microgear.connected()) {
        Serial.println("connected");

        /* Call this method regularly otherwise the connection may be lost */
        microgear.loop();
        timer = 0;
        } else {
          Serial.println("connection lost, reconnect...");
          if (timer >= 5000) {
              microgear.connect(APPID);
              timer = 0;
          }
          else timer += 100;
        }
    delay(100);
}
