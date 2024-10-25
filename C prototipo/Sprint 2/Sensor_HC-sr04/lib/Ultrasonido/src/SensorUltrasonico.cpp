#include "SensorUltrasonico.h"
#include <Arduino.h>

SensorUltrasonico::SensorUltrasonico(int triggerPin, int echoPin) : _triggerPin(triggerPin), _echoPin(echoPin) {}

void SensorUltrasonico::begin() {
    pinMode(_triggerPin, OUTPUT);
    pinMode(_echoPin, INPUT);
}

long SensorUltrasonico::readDistance() {
    digitalWrite(_triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_triggerPin, LOW);

    long duration = pulseIn(_echoPin, HIGH);
    return duration * 0.034 / 2; // Distancia en cm
}
