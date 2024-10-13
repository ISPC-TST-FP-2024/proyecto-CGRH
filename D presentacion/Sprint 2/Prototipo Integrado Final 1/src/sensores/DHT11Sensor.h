#ifndef DHT11_SENSOR_H
#define DHT11_SENSOR_H

#include <DHT.h>

class DHT11Sensor {
private:
    DHT dht;          // Objeto DHT
    int pin;          // Pin donde está conectado el sensor
    float temperature; // Variable para almacenar la temperatura
    float humidity;    // Variable para almacenar la humedad

public:
    // Constructor
    DHT11Sensor(int pin);

    // Inicializar el sensor
    void begin();

    // Leer los valores del sensor
    bool readSensor();

    // Obtener la temperatura
    float getTemperature() const;

    // Obtener la humedad
    float getHumidity() const;
};

#endif
