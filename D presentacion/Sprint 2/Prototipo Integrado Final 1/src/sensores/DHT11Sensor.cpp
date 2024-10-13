#include "DHT11Sensor.h"

#define DHTTYPE DHT11  // Tipo de sensor (DHT11)

// Constructor: inicializa el objeto DHT con el pin correspondiente
DHT11Sensor::DHT11Sensor(int pin) : dht(pin, DHTTYPE), pin(pin), temperature(0), humidity(0) {}

// Método para inicializar el sensor
void DHT11Sensor::begin() {
    dht.begin();
}

// Método para leer el sensor y almacenar los valores en las variables internas
bool DHT11Sensor::readSensor() {
    // Leer la humedad
    humidity = dht.readHumidity();
    // Leer la temperatura en grados Celsius
    temperature = dht.readTemperature();

    // Verificar si hay algún error al leer
    if (isnan(humidity) || isnan(temperature)) {
        return false; // Indica que hubo un error
    }
    return true; // Indica que la lectura fue exitosa
}

// Método para obtener la temperatura leída
float DHT11Sensor::getTemperature() const {
    return temperature;
}

// Método para obtener la humedad leída
float DHT11Sensor::getHumidity() const {
    return humidity;
}
