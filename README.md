# LED Strip Controller met ESP32

Dit project maakt gebruik van een ESP32 WROOM-32 om een WS2812B LED-strip aan te sturen, waarbij de kleuren van de LEDs worden aangepast op basis van de euro per kWh, rekening houdend met een dynamisch energiecontract. De prijzen worden opgehaald van de ENTSO-E API en omvatten inkoopkosten, energiebelasting en BTW.

## Functionaliteit

- **Individueel Aansturen van LEDs**: 48 WS2812B LEDs.
- **Dynamische Kleurverandering**: Kleurinstellingen gebaseerd op de euro per kWh per kwartier.
- **Webinterface**: Eenvoudige bediening via een webbrowser.

## Code Overzicht

- **Prijsberekening**: De totale prijs per kWh wordt berekend door de basisprijs, de marktprijs, de inkoopkosten, de energiebelasting en de BTW bij elkaar op te tellen.
- **API Integratie**: De ENTSO-E API wordt gebruikt om de day-ahead prijzen op te halen. Zorg ervoor dat je de juiste parameters instelt in de API-aanroep.
- **JSON Parsing**: De ArduinoJson-bibliotheek wordt gebruikt om de JSON-respons van de API te parseren en de relevante prijsinformatie te extraheren.
- **Kleurinstelling**: De kleur van de LED-strip wordt aangepast op basis van de geschaalde prijs, met een heatmap-kleurenschema dat van groen naar rood gaat.

## Licentie

Dit project is gelicentieerd onder de MIT-licentie. Zie het LICENSE bestand voor meer informatie.
