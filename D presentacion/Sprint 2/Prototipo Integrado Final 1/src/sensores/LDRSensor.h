#ifndef LDR_SENSOR_H
#define LDR_SENSOR_H

#include <Arduino.h>

class LDRSensor {
private:
    int signalPin;  // Pin analógico donde se conecta el LDR

public:
    // Constructor
    LDRSensor(int signalPin);

    // Inicializar el pin del LDR
    void begin();

    // Leer el valor del sensor
    int readLightLevel();
};

#endif
