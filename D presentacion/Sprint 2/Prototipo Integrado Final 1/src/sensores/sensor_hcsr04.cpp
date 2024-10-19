#include "sensor_hcsr04.h"
#include <Arduino.h>

// Definir los pines del HC-SR04 (ajusta según tu conexión)
#define PIN_TRIGGER 5  // Pin para el Trigger del sensor HC-SR04
#define PIN_ECHO 18    // Pin para el Echo del sensor HC-SR04

// Altura máxima del tanque en cm
const int ALTURA_TANQUE_CM = 100; // Ajusta según la altura real de tu tanque

void inicializarSensorNivelAgua() {
    // Configurar los pines como salida para Trigger y entrada para Echo
    pinMode(PIN_TRIGGER, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
    
    // Asegurarse de que el Trigger comience en LOW
    digitalWrite(PIN_TRIGGER, LOW);
    delay(50); // Pequeña espera para estabilizar el sensor
}

int leerNivelAgua() {
    // Enviar un pulso de Trigger (10us en HIGH)
    digitalWrite(PIN_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIGGER, LOW);

    // Leer el tiempo que tarda el eco (en microsegundos)
    long duracionEcho = pulseIn(PIN_ECHO, HIGH);

    // Convertir la duración en distancia (cm)
    int distanciaCm = duracionEcho * 0.034 / 2; // (Velocidad del sonido: 0.034 cm/us)

    // Calcular el nivel de agua en el tanque
    int nivelAguaCm = ALTURA_TANQUE_CM - distanciaCm;

    // Asegurarse de que el nivel esté dentro de los límites del tanque
    nivelAguaCm = constrain(nivelAguaCm, 0, ALTURA_TANQUE_CM);

    return nivelAguaCm;
}
