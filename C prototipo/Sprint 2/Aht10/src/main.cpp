#include <Arduino.h>
#include "SensorAHT25.h"

SensorAHT25 sensorAHT25;

void setup() {
    Serial.begin(115200);
    sensorAHT25.begin();
}

void loop() {
    float temperature = sensorAHT25.readTemperature();
    float humidity = sensorAHT25.readHumidity();

    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.print(" °C, Humedad: ");
    Serial.println(humidity);

    delay(2000); // Espera 2 segundos antes de la siguiente lectura
}
