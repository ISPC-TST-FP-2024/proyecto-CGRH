#include "PIRSensor.h"

// Constructor: inicializa el pin del sensor PIR
PIRSensor::PIRSensor(int signalPin)
    : signalPin(signalPin) {}

// Método para inicializar el pin del sensor PIR
void PIRSensor::begin() {
    pinMode(signalPin, INPUT);
}

// Método para verificar si se detecta movimiento
bool PIRSensor::isMotionDetected() {
    return digitalRead(signalPin) == HIGH; // Retorna true si se detecta movimiento
}
