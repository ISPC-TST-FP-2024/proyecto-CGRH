#ifndef HS12_SENSOR_H
#define HS12_SENSOR_H

#include <Arduino.h>

class HS12Sensor {
private:
    int signalPin;         // Pin de señal del multiplexor conectado al ESP32
    int s0Pin, s1Pin, s2Pin, s3Pin; // Pines de selección del multiplexor 74HC4067

public:
    // Constructor
    HS12Sensor(int signalPin, int s0Pin, int s1Pin, int s2Pin, int s3Pin);

    // Inicializar los pines del multiplexor
    void begin();

    // Seleccionar el canal en el multiplexor
    void selectChannel(int channel);

    // Leer el valor del sensor en el canal seleccionado
    int readSensor();
};

#endif
