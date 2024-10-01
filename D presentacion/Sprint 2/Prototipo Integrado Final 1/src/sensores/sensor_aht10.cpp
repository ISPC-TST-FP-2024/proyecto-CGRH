#include <Arduino.h>
#include "SensorAHT25.h"
#include "sensor_aht10.h"

SensorAHT25 sensorAHT25;

void iniciarAHT10() {
    sensorAHT25.begin();
}

float leerTemperaturaAHT10() {
    return sensorAHT25.readTemperature();
}

float leerHumedadAHT10() {
    return sensorAHT25.readHumidity();
}
