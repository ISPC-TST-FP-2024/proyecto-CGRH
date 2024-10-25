#include <Arduino.h>
#include "SensorUltrasonico.h"

SensorUltrasonico sensorUltrasonico(12, 13); // GPIO12 Trigger, GPIO13 Echo

void setup() {
    Serial.begin(115200);
    sensorUltrasonico.begin();
}

void loop() {
    long distance = sensorUltrasonico.readDistance();
    Serial.print("Distancia: ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(2000);
}
