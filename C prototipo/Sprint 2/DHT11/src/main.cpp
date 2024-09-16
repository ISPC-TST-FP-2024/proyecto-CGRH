#include <Arduino.h>
#include "SensorDHT11.h"

SensorDHT11 sensorDHT11(14); // GPIO14

void setup() {
    Serial.begin(115200);
    sensorDHT11.begin();
}

void loop() {
    float temperature = sensorDHT11.readTemperature();
    float humidity = sensorDHT11.readHumidity();

    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.print(" °C, Humedad: ");
    Serial.println(humidity);

    delay(2000);
}
