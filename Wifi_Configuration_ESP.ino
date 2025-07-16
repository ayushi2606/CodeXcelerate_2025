#include <WiFi.h>  

const char* ssid = "MACBOOK";
const char* password = "Vaibhav@2606";

#define LED_PIN 14  

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println();
  Serial.println("====== ESP32 WiFi Connection Demo ======");
  Serial.println("Setting up LED pin...");
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  
  Serial.println("LED pin ready.");
  
  Serial.print("Connecting to WiFi SSID: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  int attempt = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    attempt++;
    if (attempt % 10 == 0) {
      Serial.println();
      Serial.print("Still trying to connect... Attempt: ");
      Serial.println(attempt / 2);
    }
  }

  Serial.println();
  Serial.println("✅ WiFi connected successfully!");
  Serial.print("📶 IP Address: ");
  Serial.println(WiFi.localIP());

  digitalWrite(LED_PIN, HIGH);  
  Serial.println("💡 External LED turned ON (WiFi Connected)");
}

void loop() {
  
}
