#include "SensorLDR.h"
#include <Arduino.h>

SensorLDR::SensorLDR(int pin) : _pin(pin) {}

void SensorLDR::begin() {
    pinMode(_pin, INPUT);
}

int SensorLDR::readLightLevel() {
    return analogRead(_pin);
}
