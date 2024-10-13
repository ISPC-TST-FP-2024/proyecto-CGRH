#include "HCSR04Sensor.h"

// Constructor: asigna los pines TRIG y ECHO
HCSR04Sensor::HCSR04Sensor(int trigPin, int echoPin) : trigPin(trigPin), echoPin(echoPin), distance(0) {}

// Método para inicializar los pines del sensor
void HCSR04Sensor::begin() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

// Método para leer el sensor de ultrasonido y calcular la distancia
bool HCSR04Sensor::readSensor() {
    // Enviar un pulso de 10 µs al pin TRIG
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Leer el tiempo que tarda en recibir el eco
    long duration = pulseIn(echoPin, HIGH);

    // Calcular la distancia en centímetros
    distance = duration * 0.034 / 2;

    // Verificar si la medición es válida
    return (distance >= 2 && distance <= 400);
}

// Método para obtener la distancia medida
float HCSR04Sensor::getDistance() const {
    return distance;
}
