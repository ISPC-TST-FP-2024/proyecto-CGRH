#include <Arduino.h>
#include "SensorLDR.h"
#include "sensor_ldr.h"

SensorLDR sensorLDR(32);  // Pin GPIO32

void iniciarLDR() {
    sensorLDR.begin();
}

int leerNivelLuzLDR() {
    return sensorLDR.readLightLevel();
}
