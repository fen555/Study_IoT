#include <ESP8266WiFi.h>
const char* ssid = "Apple TV";
const char* password = "APPLE_TV";
const char* mqtt_server = "m12.cloudmqtt.com";

#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
SimpleTimer timer;

char auth[] = "d8a07025c5e3496e84bae6aa9b7e9091";

int stateFan;
int statLED = 0;

WiFiClient espClient;
/* Connect Wi-Fi */

/* CloudMQTT */
#include <PubSubClient.h>
PubSubClient client(espClient);
/* CloudMQTT */

/* DHT Var */
#include <DHT.h>
#define DHTPIN D5
#define DHTTYPE DHT22
DHT dht (DHTPIN, DHTTYPE);
/* DHT Var */

/* PIN Connect Relay */
#define R 16 // D0
/* PIN Connect Relay */

#define led 5 // D1

/* Server */
const char WEBSITE[] = "10.41.161.228"; // Web Server
/* Server */

/* Value to send DATA */
char msg[50]; // temp
char msg2[50]; // statFan
char msg3[50]; // statFan
/* Value to send DATA */

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

void setup()
{
  Serial.begin(115200);
  dht.begin();

  pinMode(R, OUTPUT); // Relay PIN
  pinMode(led, OUTPUT);
  Blynk.begin(auth, "Apple TV", "APPLE_TV");

  timer.setInterval(5000L, temAndHum); // ชื่อ func temAndHum
  timer.setInterval(5000L, show);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    // Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("smartfarm", "nuuloiub", "Tb_2kf9fEyzR")) {
      //      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void temAndHum () {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2, h);
}

void show () {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  Serial.println(t);
  Serial.println(h);
}

void loop() {
  Blynk.run();
  timer.run();
}
