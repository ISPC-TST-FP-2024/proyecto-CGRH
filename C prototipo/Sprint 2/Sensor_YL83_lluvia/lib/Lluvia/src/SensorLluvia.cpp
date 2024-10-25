#include "SensorLluvia.h"
#include <Arduino.h>

SensorLluvia::SensorLluvia(int pin) : _pin(pin) {}

void SensorLluvia::begin() {
    pinMode(_pin, INPUT);
}

bool SensorLluvia::isRaining() {
    return digitalRead(_pin) == LOW;
}
