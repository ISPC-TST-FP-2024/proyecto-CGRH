#include <Arduino.h>
#include "TiraLED.h"

TiraLED tiraLED(15, 8); // Pin 15, 8 LEDs

void setup() {
    Serial.begin(115200);
    tiraLED.begin();
}

void loop() {
    tiraLED.encender(strip.Color(255, 0, 0));  // Encender en rojo
    delay(1000);
    tiraLED.apagar();  // Apagar
    delay(1000);
    tiraLED.recorrer(strip.Color(0, 255, 0), 100);  // Recorrer en verde
}
