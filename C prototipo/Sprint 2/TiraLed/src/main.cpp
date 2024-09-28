/*#include <Arduino.h>
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
*/

#include <Arduino.h>
#include "TiraLED.h"

// Función para convertir RGB a uint32_t
uint32_t colorRGB(int r, int g, int b) {
  return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

TiraLED tiraLED(15, 8);  // Pin 15, 8 LEDs

void setup() {
  Serial.begin(115200);
  tiraLED.begin();  // Inicializa los LEDs
}

void loop() {
  // Convertir los valores RGB a un uint32_t y pasar ese valor a encender()
  tiraLED.encender(colorRGB(255, 0, 0));  // Enciende en rojo
  delay(1000);
  tiraLED.apagar();  // Apaga los LEDs
  delay(1000);
  
  // Convertir los valores RGB a uint32_t para recorrer()
  tiraLED.recorrer(colorRGB(0, 255, 0), 100);  // Recorre en verde
}
