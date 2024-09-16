#include <Arduino.h>
#include "SensorLDR.h"

SensorLDR sensorLDR(32); // GPIO32

void setup() {
    Serial.begin(115200);
    sensorLDR.begin();
}

void loop() {
    int lightLevel = sensorLDR.readLightLevel();
    Serial.print("Nivel de luz: ");
    Serial.println(lightLevel);
    delay(2000);
}
