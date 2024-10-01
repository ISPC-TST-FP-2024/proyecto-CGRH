#include <Wire.h>
#include <BH1750.h>
#include "sensor_bh1750.h"

BH1750 lightMeter;

void iniciarBH1750() {
    Wire.begin(21, 22);  // Pines SDA y SCL en ESP32
    if (!lightMeter.begin()) {
        Serial.println("Error al iniciar BH1750");
        while (1);
    }
    Serial.println("BH1750 iniciado correctamente.");
}

float leerLuxBH1750() {
    return lightMeter.readLightLevel();  // Retorna el nivel de luz en lux
}
