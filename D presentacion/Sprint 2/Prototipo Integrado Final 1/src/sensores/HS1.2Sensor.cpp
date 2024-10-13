#include "HS1.2Sensor.h"

// Constructor: inicializa los pines del multiplexor
HS12Sensor::HS12Sensor(int signalPin, int s0Pin, int s1Pin, int s2Pin, int s3Pin)
    : signalPin(signalPin), s0Pin(s0Pin), s1Pin(s1Pin), s2Pin(s2Pin), s3Pin(s3Pin) {}

// Método para inicializar los pines del multiplexor
void HS12Sensor::begin() {
    pinMode(signalPin, INPUT);
    pinMode(s0Pin, OUTPUT);
    pinMode(s1Pin, OUTPUT);
    pinMode(s2Pin, OUTPUT);
    pinMode(s3Pin, OUTPUT);
}

// Método para seleccionar el canal en el multiplexor
void HS12Sensor::selectChannel(int channel) {
    digitalWrite(s0Pin, channel & 0x01);
    digitalWrite(s1Pin, (channel >> 1) & 0x01);
    digitalWrite(s2Pin, (channel >> 2) & 0x01);
    digitalWrite(s3Pin, (channel >> 3) & 0x01);
}

// Método para leer el valor del sensor en el canal seleccionado
int HS12Sensor::readSensor() {
    return analogRead(signalPin);
}
