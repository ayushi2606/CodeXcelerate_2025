#include <WiFi.h>
#include <HTTPClient.h>
#include <Update.h>

const char* ssid = "MACBOOK";
const char* password = "Vaibhav@2606";
const char* update_url = "http://192.168.0.106:8000/firmwareupdates.ino.bin"; 

#define LED_PIN 14  
int blinkDelay = 1000;
unsigned long lastCheck = 0;
const unsigned long checkInterval = 30000;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  Serial.println("Firmware: Blink every 1 sec");

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi connected!");
}

void loop() {
  // Blink LED
  digitalWrite(LED_PIN, HIGH);
  delay(blinkDelay / 2);
  digitalWrite(LED_PIN, LOW);
  delay(blinkDelay / 2);

  // Check for update
  if (millis() - lastCheck > checkInterval) {
    lastCheck = millis();
    Serial.println("🔁 Checking for update...");

    if ((WiFi.status() == WL_CONNECTED)) {
      HTTPClient http;
      http.begin(update_url);
      int httpCode = http.GET();

      if (httpCode == 200) {
        int contentLength = http.getSize();
        WiFiClient* stream = http.getStreamPtr();

        if (Update.begin(contentLength)) {
          size_t written = Update.writeStream(*stream);
          if (written == contentLength && Update.end()) {
            Serial.println("✅ Update successful. Rebooting...");
            ESP.restart();
          } else {
            Serial.println("❌ Update failed.");
          }
        } else {
          Serial.println("❌ Not enough space for update.");
        }
      } else {
        Serial.printf("❌ HTTP error: %d\n", httpCode);
      }
      http.end();
    }
  }
}
