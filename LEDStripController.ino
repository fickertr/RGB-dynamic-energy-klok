#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define LED_PIN 5
#define NUM_LEDS 48
#define UPDATE_INTERVAL 900000 // 15 minuten in milliseconden

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
WebServer server(80);

const char* ssid = "YOUR_SSID"; // Vervang door je WiFi SSID
const char* password = "YOUR_PASSWORD"; // Vervang door je WiFi wachtwoord

unsigned long lastUpdate = 0;
float prices[NUM_LEDS]; // Array om prijzen voor 12 uur op te slaan
float minPrice = FLT_MAX; // Minimale prijs initialiseren
float maxPrice = FLT_MIN; // Maximale prijs initialiseren

// Definieer belastingpercentages en tarieven
const float energyTax = 0.21; // Energiebelasting (bijv. 21%)
const float VAT = 0.21; // BTW (bijv. 21%)
const float basePrice = 0.10; // Basisprijs per kWh (bijv. €0,10)

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
  minPrice = FLT_MAX; // Reset minPrice
  maxPrice = FLT_MIN; // Reset maxPrice

  for (int i = 0; i < NUM_LEDS; i++) {
    prices[i] = getEnergyPrice(); // Haal de prijs op voor elke LED
    if (prices[i] < minPrice) minPrice = prices[i]; // Update minPrice
    if (prices[i] > maxPrice) maxPrice = prices[i]; // Update maxPrice
  }
}

float getEnergyPrice() {
  HTTPClient http;
  String url = "https://api.entsoe.eu/prices?..." // Vul hier de juiste API URL in met parameters
  http.begin(url);
  int httpCode = http.GET();
  
  if (httpCode > 0) {
    String payload = http.getString();
    float marketPrice = parsePriceFromPayload(payload); // Voeg hier je parsing logica toe

    // Bereken de totale prijs inclusief belasting en BTW
    float totalPrice = basePrice + marketPrice; // Basisprijs + marktprijs
    totalPrice += totalPrice * energyTax; // Voeg energiebelasting toe
    totalPrice += totalPrice * VAT; // Voeg BTW toe

    return totalPrice; // Retourneer de totale prijs
  } else {
    Serial.println("Fout bij het ophalen van de prijs");
    return 0.0; // Fallback waarde
  }
  http.end();
}

void updateLEDs() {
  int currentHour = (millis() / UPDATE_INTERVAL / 60) % 12; // Huidige uur (0-11)
  int ledIndex = (currentHour * NUM_LEDS) / 12; // Bepaal welke LED moet worden bijgewerkt

  // Schaal de prijs naar een percentage van 0% tot 100%
  float scaledPrice = map(prices[ledIndex], minPrice, maxPrice, 0, 100);
  int colorValue = constrain(scaledPrice, 0, 100); // Zorg ervoor dat de waarde tussen 0 en 100 blijft
  uint32_t color = heatmapColor(colorValue);
  strip.setPixelColor(ledIndex, color);
  strip.show();
}

uint32_t heatmapColor(int value) {
  if (value < 50) {
    return strip.Color(0, 255, value * 5); // Van groen naar geel
  } else {
    return strip.Color((value - 50) * 5, 255, 0); // Van geel naar rood
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

// Functie om de prijs uit de payload te parseren
float parsePriceFromPayload(String payload) {
  // Voorbeeld van JSON parsing
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, payload);
  float price = doc["price"]; // Pas aan op basis van de juiste JSON-structuur
  return price;
}
