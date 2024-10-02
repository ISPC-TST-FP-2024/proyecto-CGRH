#include <Arduino.h>
#include "SensorHumedadSuelo.h"
#include "sensor_humedad_suelo.h"

SensorHumedadSuelo sensorHumedadSuelo(36);  // Pin GPIO36

void iniciarHumedadSuelo() {
    sensorHumedadSuelo.begin();
}

int leerHumedadSuelo() {
    return sensorHumedadSuelo.readHumedad();
}
