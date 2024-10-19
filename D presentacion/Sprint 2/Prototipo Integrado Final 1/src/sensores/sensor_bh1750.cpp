#include "sensor_bh1750.h"
#include <Wire.h>
#include <BH1750.h>

// Crear un objeto para el sensor BH1750
BH1750 sensorBH1750;

void inicializarSensorBH1750() {
    // Inicializar el protocolo I2C
    Wire.begin();
    
    // Inicializar el sensor BH1750 en modo de resolución alta
    if (sensorBH1750.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
        Serial.println("Sensor BH1750 iniciado correctamente");
    } else {
        Serial.println("Error al iniciar el sensor BH1750");
    }
}

uint16_t leerLuzBH1750Sensor() {
    // Leer el nivel de luz en lux
    uint16_t lux = sensorBH1750.readLightLevel();
    
    // Verificar si la lectura es válida
    if (lux == 65535) {
        Serial.println("Error al leer el sensor BH1750");
        return 0;
    }
    
    return lux;
}
