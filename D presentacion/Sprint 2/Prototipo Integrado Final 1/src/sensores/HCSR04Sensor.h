#ifndef HCSR04_SENSOR_H
#define HCSR04_SENSOR_H

#include <Arduino.h>

class HCSR04Sensor {
private:
    int trigPin;       // Pin TRIG del HC-SR04
    int echoPin;       // Pin ECHO del HC-SR04
    float distance;    // Almacena la distancia medida

public:
    // Constructor
    HCSR04Sensor(int trigPin, int echoPin);

    // Inicializar los pines del sensor
    void begin();

    // Leer la distancia medida por el sensor
    bool readSensor();

    // Obtener la distancia medida
    float getDistance() const;
};

#endif
