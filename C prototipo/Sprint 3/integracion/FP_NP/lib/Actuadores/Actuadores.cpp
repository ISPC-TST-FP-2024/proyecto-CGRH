#include "Actuadores.h"
#include <Arduino.h>

void Actuadores::configurarPin(int pin) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

void Actuadores::encender(int pin) {
    digitalWrite(pin, HIGH);
}

void Actuadores::apagar(int pin) {
    digitalWrite(pin, LOW);
}
