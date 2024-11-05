#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define LED_PIN 5
#define NUM_LEDS 48
#define UPDATE_INTERVAL 900000 // 15 minuten in milliseconden

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

const char* ssid = "YOUR_SSID"; // Vervang door je WiFi SSID
const char* password = "YOUR_PASSWORD"; // Vervang door je WiFi wachtwoord

unsigned long lastUpdate = 0;

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Verbinden met WiFi...");
  }
  Serial.println("Verbonden met WiFi");
}

void loop() {
  if (millis() - lastUpdate > UPDATE_INTERVAL) {
    lastUpdate = millis();
    float price = getEnergyPrice();
    updateLEDs(price);
  }
}

float getEnergyPrice() {
  HTTPClient http;
  http.begin("https://api.entsoe.eu/..."); // Vul hier de juiste API URL in
  int httpCode = http.GET();
  
  if (httpCode > 0) {
    String payload = http.getString();
    // Parse de JSON om de prijs te krijgen (afhankelijk van de API structuur)
    // Voorbeeld: float price = ...;
    return price; // Vervang door de juiste prijs
  } else {
    Serial.println("Fout bij het ophalen van de prijs");
    return 0.0; // Fallback waarde
  }
  http.end();
}

void updateLEDs(float price) {
  int ledIndex = (millis() / UPDATE_INTERVAL) % NUM_LEDS; // Bepaal welke LED moet worden bijgewerkt
  int colorValue = map(price, 0, 100, 0, 255); // Schaal de prijs naar een kleurwaarde

  // Bepaal de kleur op basis van een warmtebeeldcamera heatmap zonder blauw
  uint32_t color = heatmapColor(colorValue);
  strip.setPixelColor(ledIndex, color);
  strip.show();
}

uint32_t heatmapColor(int value) {
  // Kleurwaarden voor een warmtebeeldcamera-achtige heatmap zonder blauw
  if (value < 128) {
    return strip.Color(0, 255, value * 2); // Van groen naar geel
  } else {
    return strip.Color((value - 128) * 2, 255, 0); // Van geel naar rood
  }
}
