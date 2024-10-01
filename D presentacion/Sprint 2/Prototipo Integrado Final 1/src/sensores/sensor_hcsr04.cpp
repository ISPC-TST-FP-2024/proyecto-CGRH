#include <Arduino.h>
#include "SensorUltrasonico.h"
#include "sensor_hcsr04.h"

SensorUltrasonico sensorUltrasonico(12, 13);  // Pines Trigger y Echo

void iniciarUltrasonico() {
    sensorUltrasonico.begin();
}

long leerDistanciaUltrasonico() {
    return sensorUltrasonico.readDistance();
}
