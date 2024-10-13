#ifndef AHT10_SENSOR_H
#define AHT10_SENSOR_H

#include <Adafruit_AHTX0.h>

class AHT10Sensor {
private:
    Adafruit_AHTX0 aht;  // Objeto AHT10
    float temperature;   // Variable para almacenar la temperatura
    float humidity;      // Variable para almacenar la humedad

public:
    // Constructor
    AHT10Sensor();

    // Inicializar el sensor
    bool begin();

    // Leer los valores del sensor
    bool readSensor();

    // Obtener la temperatura
    float getTemperature() const;

    // Obtener la humedad
    float getHumidity() const;
};

#endif
