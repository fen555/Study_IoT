#include <ESP8266WiFi.h>
#include <PubSubClient.h>
int sensorPin = A0;
int sensorValue = 0; 

const char* ssid = "Apple TV";
const char* password = "APPLE_TV";
const char* mqtt_server = "m12.cloudmqtt.com";

char msg[50];

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
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
    if (client.connect("soil", "wvottqye", "tr8fy-KkiXay")) { // topic,username,password
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("iot", "Start");
      // ... and resubscribe
      //client.subscribe("Node2");
      client.publish("/checkSoil", "Hi");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
if (!client.connected()) {
    reconnect();
  }
  client.loop();

  char so[50];
  sensorValue = analogRead(sensorPin);    

  Serial.print("Moisture of Soil:  ");
  Serial.println(sensorValue);

  itoa(sensorValue,so,10);
  snprintf (msg,75,so);
  client.publish("/checkSoil", msg);
  Serial.print("MSG:  ");
  Serial.println(msg);
  delay(1000);

}
