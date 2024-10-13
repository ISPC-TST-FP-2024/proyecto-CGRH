#include "LDRSensor.h"

// Constructor: inicializa el pin del sensor LDR
LDRSensor::LDRSensor(int signalPin)
    : signalPin(signalPin) {}

// Método para inicializar el pin del sensor LDR
void LDRSensor::begin() {
    pinMode(signalPin, INPUT);
}

// Método para leer el nivel de luz desde el LDR
int LDRSensor::readLightLevel() {
    return analogRead(signalPin);
}
