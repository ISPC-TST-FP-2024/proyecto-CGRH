#include "sensor_dht11.h"
#include <Arduino.h>
#include <DHT.h>

// Definir el pin de datos del DHT11
#define PIN_DHT11 21  // Cambia este valor según el pin donde está conectado el sensor

// Definir el tipo de sensor (DHT11)
#define DHTTYPE DHT11

// Crear un objeto DHT
DHT dht(PIN_DHT11, DHTTYPE);

void inicializarSensorDHT11() {
    // Inicializar el sensor DHT11
    dht.begin();
}

float leerTemperatura() {
    // Leer la temperatura del sensor DHT11
    float temperatura = dht.readTemperature();
    
    // Comprobar si la lectura es válida
    if (isnan(temperatura)) {
        Serial.println("Error al leer la temperatura del sensor DHT11");
        return 0.0;  // Devolver un valor por defecto en caso de error
    }
    
    return temperatura;
}

float leerHumedad() {
    // Leer la humedad del sensor DHT11
    float humedad = dht.readHumidity();
    
    // Comprobar si la lectura es válida
    if (isnan(humedad)) {
        Serial.println("Error al leer la humedad del sensor DHT11");
        return 0.0;  // Devolver un valor por defecto en caso de error
    }
    
    return humedad;
}
