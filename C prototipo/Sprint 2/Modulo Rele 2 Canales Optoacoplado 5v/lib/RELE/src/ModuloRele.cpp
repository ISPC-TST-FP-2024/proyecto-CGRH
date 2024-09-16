#include "ModuloRele.h"
#include <Arduino.h>

ModuloRele::ModuloRele(int pin) : _pin(pin) {}

void ModuloRele::begin() {
    pinMode(_pin, OUTPUT);
    apagar(); // Iniciar con el relé apagado
}

void ModuloRele::encender() {
    digitalWrite(_pin, LOW); // Activa el relé (depende del tipo de relé)
}

void ModuloRele::apagar() {
    digitalWrite(_pin, HIGH); // Desactiva el relé
}
