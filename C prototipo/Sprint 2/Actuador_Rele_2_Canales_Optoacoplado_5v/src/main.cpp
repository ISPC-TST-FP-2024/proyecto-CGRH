#include <Arduino.h>
#include "ModuloRele.h"

ModuloRele rele1(4);  // GPIO4 para el primer relé

void setup() {
    Serial.begin(115200);
    rele1.begin();
}

void loop() {
    rele1.encender();
    Serial.println("Relé encendido.");
    delay(2000);

    rele1.apagar();
    Serial.println("Relé apagado.");
    delay(2000);
}
