#ifndef PIR_SENSOR_H
#define PIR_SENSOR_H

#include <Arduino.h>

class PIRSensor {
private:
    int signalPin; // Pin digital donde se conecta el sensor PIR

public:
    // Constructor
    PIRSensor(int signalPin);

    // Inicializar el pin del sensor PIR
    void begin();

    // Leer el estado del sensor (movimiento detectado o no)
    bool isMotionDetected();
};

#endif
