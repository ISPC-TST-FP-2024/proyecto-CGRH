#include <Arduino.h>
#include "SensorDHT11.h"
#include "sensor_dht11.h"

SensorDHT11 sensorDHT11(14);  // Pin GPIO14

void iniciarDHT11() {
    sensorDHT11.begin();
}

float leerTemperaturaDHT11() {
    return sensorDHT11.readTemperature();
}

float leerHumedadDHT11() {
    return sensorDHT11.readHumidity();
}
