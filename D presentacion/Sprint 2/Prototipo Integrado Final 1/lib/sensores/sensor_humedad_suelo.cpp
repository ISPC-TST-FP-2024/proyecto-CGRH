#include "sensor_humedad_suelo.h"
#include <Arduino.h>

// Definir el pin donde está conectado el sensor de humedad de suelo (ajusta el pin según tu hardware)
#define PIN_SENSOR_HUMEDAD_SUELO 34

// Valores de calibración para el sensor
const int HUMEDAD_MAXIMA_ADC = 1800;  // Valor aproximado del ADC con suelo completamente seco (ajusta según tu sensor)
const int HUMEDAD_MINIMA_ADC = 300;   // Valor aproximado del ADC con suelo completamente húmedo (ajusta según tu sensor)

void inicializarSensorHumedadSuelo() {
    // Configura el pin del sensor de humedad como entrada analógica
    pinMode(PIN_SENSOR_HUMEDAD_SUELO, INPUT);
}

int leerHumedadSuelo() {
    // Lee el valor analógico del sensor de humedad
    int valorADC = analogRead(PIN_SENSOR_HUMEDAD_SUELO);

    // Convierte el valor ADC en un porcentaje de humedad (0% = suelo completamente seco, 100% = suelo completamente húmedo)
    int porcentajeHumedad = map(valorADC, HUMEDAD_MAXIMA_ADC, HUMEDAD_MINIMA_ADC, 0, 100);

    // Asegúrate de que el porcentaje esté dentro de los límites válidos
    porcentajeHumedad = constrain(porcentajeHumedad, 0, 100);

    return porcentajeHumedad;
}
