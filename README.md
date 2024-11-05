# LED Strip Controller met ESP32

Dit project gebruikt een ESP32 WROOM-32 om een WS2812 LED-strip aan te sturen, waarbij de kleuren van de LEDs worden aangepast op basis van energieprijzen van de ENTSO-E API. De LED-index verandert afhankelijk van de tijd, zodat elke LED een specifieke tijd vertegenwoordigt.

## Functionaliteit

- **LED Aansturing**: 48 WS2812 LEDs.
- **Dynamische Kleurverandering**: Kleurinstellingen gebaseerd op energieprijzen.
- **Webinterface**: Eenvoudige bediening via een webbrowser.

## Benodigdheden

- ESP32 WROOM-32
- WS2812 LED-strip (48 LEDs)
- Arduino IDE
- WiFi-verbinding

## Installatie

1. **Arduino IDE**: Zorg ervoor dat je de Arduino IDE hebt geïnstalleerd.
2. **Bibliotheken**: Installeer de volgende bibliotheken:
   - Adafruit NeoPixel
   - WiFi
   - WebServer
   - HTTPClient
3. **Code**: Plaats de code in een nieuw sketch-bestand (`LEDStripController.ino`).
4. **Configuratie**: Vervang `YOUR_SSID` en `YOUR_PASSWORD` door je WiFi-gegevens.
5. **Uploaden**: Selecteer het juiste bord en de juiste poort in de Arduino IDE en upload de code naar de ESP32.

## Gebruik

- Na het uploaden, open je een webbrowser en voer je het IP-adres van de ESP32 in om de webinterface te openen.
- Klik op de link om de LED-strip bij te werken met de nieuwste energieprijzen.

## Code Overzicht

- **LED Indexing**: De LED-index wordt berekend op basis van het huidige uur, waarbij de index verschuift voor een 12-uurs vooruitzicht.
- **Kleurinstelling**: Kleurwaarden worden geschaald van 0 tot 255 op basis van de energieprijs, met een heatmap-kleurenschema.

## Licentie

Dit project is gelicentieerd onder de MIT-licentie. Zie het LICENSE bestand voor meer informatie.
