#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>

#define LED_PIN 5
#define NUM_LEDS 48
#define UPDATE_INTERVAL 900000 // 15 minuten in milliseconden

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
WebServer server(80);

const char* ssid = "YOUR_SSID"; // Vervang door je WiFi SSID
const char* password = "YOUR_PASSWORD"; // Vervang door je WiFi wachtwoord

unsigned long lastUpdate = 0;
float prices[NUM_LEDS]; // Array om prijzen voor 12 uur op te slaan

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

  server.on("/", handleRoot);
  server.on("/update", handleUpdate);
  server.begin();
}

void loop() {
  server.handleClient();
  if (millis() - lastUpdate > UPDATE_INTERVAL) {
    lastUpdate = millis();
    updatePrices();
    updateLEDs();
  }
}

void updatePrices() {
  for (int i = 0; i < NUM_LEDS; i++) {
    prices[i] = getEnergyPrice(i); // Haal de prijs op voor elke LED
  }
}

float getEnergyPrice(int hourOffset) {
  HTTPClient http;
  String url = "https://api.entsoe.eu/..."; // Vul hier de juiste API URL in
  // Voeg hier logica toe om de juiste prijs op te halen op basis van hourOffset
  http.begin(url);
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

void updateLEDs() {
  int currentHour = (millis() / UPDATE_INTERVAL / 60) % 24; // Huidige uur
  int ledIndex = (currentHour + 12) % NUM_LEDS; // Bepaal welke LED moet worden bijgewerkt

  // Bepaal de kleur op basis van de energieprijs
  int colorValue = map(prices[ledIndex], 0, 100, 0, 255); // Schaal de prijs naar een kleurwaarde
  uint32_t color = heatmapColor(colorValue);
  strip.setPixelColor(ledIndex, color);
  strip.show();
}

uint32_t heatmapColor(int value) {
  if (value < 128) {
    return strip.Color(0, 255, value * 2); // Van groen naar geel
  } else {
    return strip.Color((value - 128) * 2, 255, 0); // Van geel naar rood
  }
}

void handleRoot() {
  String html = "<html><body><h1>LED Strip Controller</h1>";
  html += "<p><a href=\"/update\">Update LED Strip</a></p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleUpdate() {
  updatePrices();
  server.send(200, "text/plain", "LED Strip Updated with new prices.");
}
