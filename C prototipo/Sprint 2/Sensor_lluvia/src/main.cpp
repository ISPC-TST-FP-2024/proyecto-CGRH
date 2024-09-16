#include <Arduino.h>
#include "SensorLluvia.h"

SensorLluvia sensorLluvia(33); // GPIO33

void setup() {
    Serial.begin(115200);
    sensorLluvia.begin();
}

void loop() {
    if (sensorLluvia.isRaining()) {
        Serial.println("Está lloviendo.");
    } else {
        Serial.println("No está lloviendo.");
    }
    delay(2000);
}
