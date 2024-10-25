#ifndef MOISTURE_SENSOR_H
#define MOISTURE_SENSOR_H

#include <Arduino.h>

class MoistureSensor {
public:
    MoistureSensor(uint8_t pin);  // Constructor
    void begin();                  // Inicializa el sensor
    int readMoisture();           // Lee el nivel de humedad (0-100%)

private:
    uint8_t _pin;                 // Pin conectado al sensor
};

#endif // MOISTURE_SENSOR_H
