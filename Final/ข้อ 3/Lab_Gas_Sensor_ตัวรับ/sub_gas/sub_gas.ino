#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "Apple TV";
const char* password = "APPLE_TV";

#define mqtt_server "m12.cloudmqtt.com"
#define mqtt_port 10250
#define mqtt_user "wvottqye"
#define mqtt_password "tr8fy-KkiXay"
float oldTemp = 0.0;
WiFiClient espClient;
PubSubClient client(espClient);
void setup() {
  pinMode(D1, OUTPUT);
  Serial.begin(115200);
  delay(10);

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
}

void callback(char* topic, byte* payload, unsigned int length) {
  String msg = "";
  String to = "";
  int i = 0;
  while (i < length) msg += (char)payload[i++];
  to = topic;
  if (to == "/checkGas") {
    Serial.println(msg);
    if (msg.toFloat() > 2) {
      digitalWrite(D1, HIGH);
      Serial.print(msg.toFloat());
    } else {
      digitalWrite(D1, LOW);
    }
  } 
}
