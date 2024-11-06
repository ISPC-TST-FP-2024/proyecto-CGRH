#include "Sensor_nivel.h"
#include <Arduino.h>

int Sensor_nivel::medirNivelAgua(int triggerPin, int echoPin) {
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    long duracion = pulseIn(echoPin, HIGH);
    return duracion * 0.034 / 2;
}
