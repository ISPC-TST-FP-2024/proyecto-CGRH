#include "sensor.h"

// Constructor de la clase Sensor
Sensor_DHT11::Sensor_DHT11(int dhtPin, int dhtType, int ledPin, int numPixels) 
    : dhtPin(dhtPin), dhtType(dhtType), ledPin(ledPin), numPixels(numPixels), 
      dht(dhtPin, dhtType), strip(numPixels, ledPin, NEO_GRB + NEO_KHZ800) {}

// Método para inicializar el sensor DHT y los LEDs
void Sensor_DHT11::begin() {
    dht.begin();  // Inicializar el sensor DHT
    strip.begin();  // Inicializar el LED WS2812
    strip.show();   // Apagar todos los LEDs inicialmente
}

// Método para leer datos de temperatura y humedad
void Sensor_DHT11::leerDatos() {
    float temperatura = dht.readTemperature();
    float humedad = dht.readHumidity();
    
    if (isnan(temperatura) || isnan(humedad)) {
        Serial.println("Error en la lectura del sensor DHT11");
        return;
    }

    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.print(" C, Humedad: ");
    Serial.print(humedad);
    Serial.println(" %");
}

// Método para actualizar el LED según la temperatura
void Sensor_DHT11::actualizarLED() {
    float temperatura = dht.readTemperature();
    
    if (temperatura > 30) {
        strip.setPixelColor(0, strip.Color(255, 0, 0));  // Rojo si temperatura > 30°C
    } else {
        strip.setPixelColor(0, strip.Color(0, 255, 0));  // Verde si temperatura <= 30°C
    }
    strip.show();
}
