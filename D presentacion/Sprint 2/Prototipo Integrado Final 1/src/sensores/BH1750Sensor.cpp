#include "BH1750Sensor.h"

// Constructor: inicializa la variable de lux a cero
BH1750Sensor::BH1750Sensor() : lux(0) {}

// Método para inicializar el sensor
bool BH1750Sensor::begin() {
    Wire.begin();
    return lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);
}

// Método para leer el sensor y almacenar el valor en la variable interna
bool BH1750Sensor::readSensor() {
    float reading = lightMeter.readLightLevel();

    // Verificar si la lectura es válida
    if (isnan(reading)) {
        return false; // Indica que hubo un error
    }

    // Almacenar el valor leído
    lux = reading;
    return true; // Indica que la lectura fue exitosa
}

// Método para obtener la lectura de luz
float BH1750Sensor::getLux() const {
    return lux;
}
