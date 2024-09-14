#include <Arduino.h>
#include "SensorHumedadSuelo.h"

SensorHumedadSuelo sensorHumedadSuelo(36); // GPIO36

void setup() {
    Serial.begin(115200);
    sensorHumedadSuelo.begin();
}

void loop() {
    int humedad = sensorHumedadSuelo.readHumedad();
    Serial.print("Humedad del suelo: ");
    Serial.println(humedad);
    delay(2000);
}
