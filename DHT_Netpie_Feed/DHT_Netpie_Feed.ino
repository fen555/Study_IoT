#include <DHT.h>
#include <ESP8266WiFi.h>
#include <MicroGear.h>

const char* ssid     = "vaseline";
const char* password = "mmm02333";

#define APPID "COFEN" 
#define KEY "pjdeqj4XylKD7LI" //device key แต่ในเว็บ netpie ใช้ session key
#define SECRET "vTxlt4B4shgvDsvvXBmvM0ieQ"  //
#define FEEDID  "test22"                    //
#define ALIAS   "piedht"


WiFiClient client;
int timer = 0;
char str[32];  
#define DHTTYPE DHT22                    //Define sensor type
#define DHTPIN D4                        // Define sensor pin
DHT dht(DHTPIN, DHTTYPE);               //Initialize DHT sensor
float humid;
float temp;  

MicroGear microgear(client);
void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
  Serial.print("Incoming message --> ");
  msg[msglen] = '\0';
  Serial.println((char *)msg);
}

void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
  Serial.println("Connected to NETPIE...");
  microgear.setAlias(ALIAS);
}

void setup() {
  dht.begin();
  microgear.on(MESSAGE,onMsghandler);
  microgear.on(CONNECTED,onConnected);      //optional
  microgear.on(ERROR,onConnected);
  microgear.on(INFO,onConnected);
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
  Serial.print("*");
  microgear.loop();
  if (timer >= 15000) {
  humid = dht.readHumidity();
  temp = dht.readTemperature();  
  sprintf(str,"%d,%d",humid,temp);
  Serial.println(str);  
  String data = "{\"humidity\":";
  data += humid ;
  data += ",\"temperature\":";
  data += temp ;
  data += "}";
  Serial.println((char*) data.c_str());
    if (isnan(humid) || isnan(temp) || humid >= 200 || temp>= 200) {
      Serial.println("Failed to read from DHT sensor!");
    }else{
      Serial.print("Sending --> ");  
      microgear.writeFeed(FEEDID,data);     //YOUR  FEED ID, API KEY
    }
  timer = 0;
  } 
  else timer += 200;
 } else {
   Serial.println("connection lost, reconnect...");
  if (timer >= 5000) {
    microgear.connect(APPID);
    timer = 0;
  }
  else timer += 200;
  }
  delay(200);
}
