#define BLYNK_TEMPLATE_ID "TMPL3-cNkDjL5"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "TaIg7TikhZekreujHQxlVsEkDqJxU3Gs"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char ssid[] = "VIRAT 4";
char pass[] = "virat@555";

// DHT11 configuration
#define DHTPIN 4           
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V0, t);  
  Blynk.virtualWrite(V1, h);  

  Serial.print("Temp: ");
  Serial.print(t);
  Serial.print(" °C | Humidity: ");
  Serial.print(h);
  Serial.println(" %");
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  dht.begin();
  timer.setInterval(10000L, sendSensor); 
}

void loop() {
  Blynk.run();
  timer.run();
}
