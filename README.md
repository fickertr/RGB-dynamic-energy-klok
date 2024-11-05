# LED Strip Controller met ESP32

Dit project maakt gebruik van een ESP32 WROOM-32 om een WS2812B LED-strip aan te sturen, waarbij de kleuren van de LEDs worden aangepast op basis van de euro per kWh, rekening houdend met een dynamisch energiecontract. De prijzen worden opgehaald van de ENTSO-E API en omvatten inkoopkosten, energiebelasting en BTW.

## Functionaliteit

- **Individueel Aansturen van LEDs**: 48 WS2812B LEDs.
- **Dynamische Kleurverandering**: Kleurinstellingen gebaseerd op de euro per kWh per kwartier.
- **Webinterface**: Eenvoudige bediening via een webbrowser.

## Benodigdheden

- ESP32 WROOM-32
- WS2812B LED-strip (48 LEDs)
- Arduino IDE
- WiFi-verbinding
- ArduinoJson-bibliotheek

## Installatie

1. **Arduino IDE**: Zorg ervoor dat je de Arduino IDE hebt geïnstalleerd.
2. **Bibliotheken**: Installeer de volgende bibliotheken via de Library Manager:
   - Adafruit NeoPixel
   - WiFi
   - WebServer
   - HTTPClient
   - ArduinoJson
3. **Code**: Plaats de code in een nieuw sketch-bestand (`LEDStripController.ino`).
4. **Configuratie**: Vervang `YOUR_SSID` en `YOUR_PASSWORD` door je eigen WiFi-gegevens. Vul de juiste API-URL in de `getEnergyPrice` functie in.
5. **Uploaden**: Selecteer het juiste bord en de juiste poort in de Arduino IDE en upload de code naar de ESP32.

## Gebruik

- Na het uploaden, open je een webbrowser en voer je het IP-adres van de ESP32 in om de webinterface te openen.
- Klik op de link om de LED-strip bij te werken met de nieuwste energieprijzen.

## Code Overzicht

- **Prijsberekening**: De totale prijs per kWh wordt berekend door de basisprijs, de marktprijs, de inkoopkosten, de energiebelasting en de BTW bij elkaar op te tellen.
- **Kleurinstelling**: De kleur van de LED-strip wordt aangepast op basis van de geschaalde prijs, met een heatmap-kleurenschema.

## Licentie

Dit project is gelicentieerd onder de MIT-licentie. Zie het LICENSE bestand voor meer informatie.
