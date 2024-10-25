#include "SensorHumedadSuelo.h"
#include <Arduino.h>

SensorHumedadSuelo::SensorHumedadSuelo(int pin) : _pin(pin) {}

void SensorHumedadSuelo::begin() {
    pinMode(_pin, INPUT);
}

int SensorHumedadSuelo::readHumedad() {
    return analogRead(_pin);
}
