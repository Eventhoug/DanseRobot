# Danserobot
Koden er uploadet til github vha Claude ellers er koden skrevet af os

Arduino-kode til en lille robot med fire servoer (to ben og to fødder), der skiftevis danser og går sidelæns.

## Hardware

- Arduino Uno Mini (`uno_mini`)
- 4 servoer

| Servo      | Pin | Standardposition |
|------------|-----|------------------|
| Venstre fod | 11 | 110° |
| Venstre ben | 6  | 145° |
| Højre ben   | 5  | 30°  |
| Højre fod   | 3  | 80°  |

Den indbyggede LED lyser, mens robotten bevæger sig.

## Byg og upload

Projektet bruger [PlatformIO](https://platformio.org/) i VS Code. Åbn mappen, og klik på **Upload** i PlatformIO-værktøjslinjen, eller kør:

```
pio run --target upload
```
