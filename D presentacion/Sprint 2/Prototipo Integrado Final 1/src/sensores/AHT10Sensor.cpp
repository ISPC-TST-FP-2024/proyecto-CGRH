#include "AHT10Sensor.h"

// Constructor: inicializa las variables de temperatura y humedad a cero
AHT10Sensor::AHT10Sensor() : temperature(0), humidity(0) {}

// Método para inicializar el sensor
bool AHT10Sensor::begin() {
    return aht.begin();
}

// Método para leer el sensor y almacenar los valores en las variables internas
bool AHT10Sensor::readSensor() {
    sensors_event_t humidity_event, temp_event;

    // Leer el sensor
    aht.getEvent(&humidity_event, &temp_event);

    // Verificar si los datos son válidos
    if (isnan(humidity_event.relative_humidity) || isnan(temp_event.temperature)) {
        return false; // Indica que hubo un error
    }

    // Almacenar los datos leídos
    humidity = humidity_event.relative_humidity;
    temperature = temp_event.temperature;
    return true; // Indica que la lectura fue exitosa
}

// Método para obtener la temperatura leída
float AHT10Sensor::getTemperature() const {
    return temperature;
}

// Método para obtener la humedad leída
float AHT10Sensor::getHumidity() const {
    return humidity;
}
