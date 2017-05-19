
#include "ESP8266WiFi.h"
#include <PubSubClient.h>
#include "DHT.h"
#define DHTPIN 2    // what digital pin we're connected to
                    //pin2 to D4 on esp board

#define DHTTYPE DHT22  // DHT 22
int sensorPin = A0;
int sensorValue = 0; 

DHT dht(DHTPIN,DHTTYPE);


const char WEBSITE[] = "api.pushingbox.com"; //pushingbox API server
const String devid = "v93F52AF4976BEEC"; //device ID from Pushingbox 

const char* ssid = "Apple TV";
const char* password = "APPLE_TV";
WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  dht.begin();

}


void loop()
{
  
  //Wait between measurements longer then normal to slow donwn
  //google sheet populate, as We dont want to exceed free service quota
  delay(1000); //10 seconds, (sampling rate vs. service call quota)

  float humidityData = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float celData = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float fehrData = dht.readTemperature(true);
  float din = sensorValue = analogRead(sensorPin);
  // Check if any reads failed and exit early (to try again).
  if (isnan(humidityData) || isnan(celData) || isnan(fehrData))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float hicData = dht.computeHeatIndex(celData, humidityData, false);
  // Compute heat index in Fahrenheit (the default)
  float hifData = dht.computeHeatIndex(fehrData, humidityData);

  //Print to Serial monitor or Terminal of your chocice at 115200 Baud
  Serial.print("Humidity: ");
  Serial.print(humidityData);
  Serial.print(" %\t");
  Serial.print("Temperature in Cel: ");
  Serial.print(celData);
  Serial.print(" *C ");
  Serial.print("Temperature in Fehr: ");
  Serial.print(din);
  
  Serial.print("\n");
    
  WiFiClient client;  //Instantiate WiFi object

    //Start or API service using our WiFi Client through PushingBox
    if (client.connect(WEBSITE, 80))
      { 
        Serial.print("11");
         client.print("GET /pushingbox?devid=" + devid
       + "&humidityData=" + (String) humidityData
       + "&celData="      + (String) celData
       + "&fehrData="     + (String) din
 
         );

      client.println(" HTTP/1.1"); 
      client.print("Host: ");
      client.println(WEBSITE);
      client.println("User-Agent: ESP8266/1.0");
      client.println("Connection: close");
      client.println();
      }
}
