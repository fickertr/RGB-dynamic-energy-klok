# LED Strip Controller met ESP32

Dit project maakt gebruik van een ESP32 WROOM-32 om een WS2812 LED-strip aan te sturen. De LED-strip verandert van kleur op basis van de energieprijzen die worden opgehaald van de ENTSO-E API. De kleuren zijn geïnspireerd door een warmtebeeldcamera.

## Inhoud

- Kenmerken
- Benodigdheden
- Installatie
- Gebruik
- Licentie

## Kenmerken

- Aansturing van een WS2812 LED-strip met 48 LEDs.
- Kleurverandering op basis van energieprijzen.
- Eenvoudige webinterface voor bediening.
- Kleurenschema geïnspireerd door warmtebeeldcamera's.

## Benodigdheden

- ESP32 WROOM-32
- WS2812 LED-strip (48 LEDs)
- Arduino IDE
- WiFi-verbinding

## Installatie

1. **Arduino IDE**: Zorg ervoor dat je de Arduino IDE hebt geïnstalleerd.
2. **Bibliotheken**: Installeer de volgende bibliotheken via de Library Manager:
   - Adafruit NeoPixel
   - WiFi
   - WebServer
   - HTTPClient
3. **Code**: Kopieer de code uit `LEDStripController.ino` en plak deze in de Arduino IDE.
4. **Configuratie**: Vervang `YOUR_SSID` en `YOUR_PASSWORD` door je eigen WiFi-gegevens.
5. **Uploaden**: Selecteer het juiste bord en de juiste poort in de Arduino IDE en upload de code naar de ESP32.

## Gebruik

- Zodra de ESP32 is verbonden met WiFi, open je een webbrowser en voer je het IP-adres van de ESP32 in om de webinterface te openen.
- Klik op de link om de LED-strip bij te werken met de nieuwste energieprijs.

## Licentie

Dit project is gelicentieerd onder de MIT-licentie. Zie het LICENSE bestand voor meer informatie.
