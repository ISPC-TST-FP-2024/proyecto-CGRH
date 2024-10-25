#include "MoistureSensor.h"

// Constructor
MoistureSensor::MoistureSensor(uint8_t pin) : _pin(pin) {}

// Inicializa el sensor
void MoistureSensor::begin() {
    pinMode(_pin, INPUT);  // Configura el pin como entrada
}

// Lee el nivel de humedad (0-100%)
int MoistureSensor::readMoisture() {
    int sensorValue = analogRead(_pin);  // Lee el valor analógico
    int moisturePercent = map(sensorValue, 0, 4095, 0, 100);  // Convierte a porcentaje
    return moisturePercent;               // Devuelve el porcentaje de humedad
}
