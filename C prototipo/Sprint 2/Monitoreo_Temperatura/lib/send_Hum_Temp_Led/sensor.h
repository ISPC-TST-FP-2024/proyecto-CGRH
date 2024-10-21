#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_NeoPixel.h>

class Sensor_DHT11 {
public:
    Sensor_DHT11(int dhtPin, int dhtType, int ledPin, int numPixels);  // Constructor
    void begin();                       // Método para inicializar el sensor y el LED
    void leerDatos();                   // Método para leer datos del sensor
    void actualizarLED();              // Método para actualizar el color del LED

private:
    int dhtPin;                        // Pin del DHT11
    int ledPin;                        // Pin del LED WS2812
    int numPixels;                     // Número de LEDs WS2812
    int dhtType;                       // Tipo de DHT (por ejemplo, DHT11)

    DHT dht;                           // Objeto del sensor DHT
    Adafruit_NeoPixel strip;           // Objeto del LED WS2812

    float leerHumedad();               // Método para leer la humedad
    float leerTemperatura();           // Método para leer la temperatura
};

#endif
