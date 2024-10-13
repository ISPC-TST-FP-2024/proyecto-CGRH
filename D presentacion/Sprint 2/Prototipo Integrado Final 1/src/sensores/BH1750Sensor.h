#ifndef BH1750_SENSOR_H
#define BH1750_SENSOR_H

#include <Wire.h>
#include <BH1750.h>

class BH1750Sensor {
private:
    BH1750 lightMeter;  // Objeto BH1750
    float lux;          // Variable para almacenar la lectura de luz en lux

public:
    // Constructor
    BH1750Sensor();

    // Inicializar el sensor
    bool begin();

    // Leer los valores del sensor
    bool readSensor();

    // Obtener la lectura de luz
    float getLux() const;
};

#endif
