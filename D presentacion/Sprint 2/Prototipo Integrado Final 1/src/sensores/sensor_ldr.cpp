#include "sensor_ldr.h"
#include <Arduino.h>

// Pin donde está conectado el LDR
int pinLDRGlobal;

// Función para inicializar el sensor LDR
void inicializarSensorLDR(int pinLDR) {
    pinLDRGlobal = pinLDR; // Guardamos el pin donde está conectado el LDR
    pinMode(pinLDRGlobal, INPUT);
    Serial.println("Sensor LDR inicializado");
}

// Función para leer el valor del sensor LDR
int leerLuzLDR() {
    // Leer el valor analógico del LDR
    int valorLDR = analogRead(pinLDRGlobal);

    // Imprimir el valor en el serial para depuración
    Serial.print("Valor LDR: ");
    Serial.println(valorLDR);

    // Devolver el valor leído
    return valorLDR;
}
