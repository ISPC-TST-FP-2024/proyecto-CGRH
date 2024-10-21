#include "sensor_aht10.h"
#include <Wire.h>
#include <AHT10.h>

// Crear un objeto para el sensor AHT10
AHT10 sensorAHT10;

void inicializarSensorAHT10() {
    // Inicializar el protocolo I2C
    Wire.begin();

    // Inicializar el sensor AHT10
    if (sensorAHT10.begin()) {
        Serial.println("Sensor AHT10 iniciado correctamente");
    } else {
        Serial.println("Error al iniciar el sensor AHT10");
    }
}

float leerTemperaturaAHT10() {
    // Leer la temperatura desde el sensor
    float temperatura = sensorAHT10.readTemperature();

    // Verificar si la lectura es válida
    if (isnan(temperatura)) {
        Serial.println("Error al leer la temperatura del sensor AHT10");
        return 0.0;
    }

    return temperatura;
}

float leerHumedadAHT10() {
    // Leer la humedad desde el sensor
    float humedad = sensorAHT10.readHumidity();

    // Verificar si la lectura es válida
    if (isnan(humedad)) {
        Serial.println("Error al leer la humedad del sensor AHT10");
        return 0.0;
    }

    return humedad;
}
