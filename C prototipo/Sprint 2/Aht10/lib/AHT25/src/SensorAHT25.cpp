#include "SensorAHT25.h"

SensorAHT25::SensorAHT25() {}

void SensorAHT25::begin() {
    if (!aht.begin()) {
        Serial.println("AHT25 no encontrado");
    }
}

float SensorAHT25::readTemperature() {
    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp);
    return temp.temperature;
}

float SensorAHT25::readHumidity() {
    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp);
    return humidity.relative_humidity;
}
