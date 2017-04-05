#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Apple TV";
const char* password = "APPLE_TV";
const char* mqtt_server = "m12.cloudmqtt.com";

char msg[50];

WiFiClient espClient;
PubSubClient client(espClient);


void setup(){
  Serial.begin(115200);
  pinMode(D1, INPUT);
  setup_wifi();
  client.setServer(mqtt_server, 10250); //port ใน mqtt
  client.setCallback(callback);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("pir", "wvottqye", "tr8fy-KkiXay")) { // topic,username,password
      Serial.println("connected");
      // Once connected, publish an announcement...
     // client.publish("iot", "Start");
      // ... and resubscribe
      //client.subscribe("Node2");
     // client.publish("/checkPIR", "Hi");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void loop(){
  int value= digitalRead(D1);
  //Serial.println(value);
//  if (value == HIGH)
//  {
//    Serial.println("yes");
//    //delay(1000) ;
//  }
//
//  else
//  {
//    Serial.println("no");
//  }

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

 // char gas[50];
  
//  float sensor_volt;
//  float sensorValue;

 // sensorValue = analogRead(A0);
 // sensor_volt = sensorValue / 1024 * 5.0;


  delay(1000);
 // itoa(sensor_volt,gas,10);
 // snprintf (msg,75,value);
 //msg = value;
 //String msg = String(value, DEC);
 //Serial.println(msg);
 if (value == HIGH)
  {
    client.publish("/checkPIR", "1");
    Serial.println("yes");
    //delay(1000) ;
  }
  else
  {
    client.publish("/checkPIR", "0");
    Serial.println("no");
  }
//  client.publish("/checkPIR", msg);
}
