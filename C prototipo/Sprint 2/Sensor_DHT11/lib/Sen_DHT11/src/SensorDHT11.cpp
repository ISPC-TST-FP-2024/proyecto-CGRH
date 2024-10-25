#include "SensorDHT11.h"

SensorDHT11::SensorDHT11(int pin) : dht(pin, DHT11) {}

void SensorDHT11::begin() {
    dht.begin();
}

float SensorDHT11::readTemperature() {
    return dht.readTemperature();
}

float SensorDHT11::readHumidity() {
    return dht.readHumidity();
}
