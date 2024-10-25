#include "SensorDHT11.h"

SensorDHT11::SensorDHT11(int pin) : dht(pin, DHT11) {}

void SensorDHT11::begin() {
    dht.begin();
}

float SensorDHT11::readTemperature() {
    float temp = dht.readTemperature();
    if (isnan(temp)) {
        Serial.println("Error al leer la temperatura");
    }
    return temp;
}

float SensorDHT11::readHumidity() {
    float hum = dht.readHumidity();
    if (isnan(hum)) {
        Serial.println("Error al leer la humedad");
    }
    return hum;
}