#include <Arduino.h>
#include <NewPing.h>
#include "MyLoRaWan.h"  // Asegúrate de que coincide con el nombre del archivo
#include <ESP32_LoRaWAN.h>

#define VextPin 21 // Cambiado de Vext a VextPin


// Definición de pines para el sensor ultrasónico
#define TRIGGER_PIN 13
#define ECHO_PIN 12
#define MAX_DISTANCE 200  // Máxima distancia de detección (en cm)

// Definición del pin del relé para controlar la bomba
#define RELAY_PIN 5

// Umbral de nivel de agua en centímetros
#define WATER_THRESHOLD 50

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
MyLoRaWanClass loraWan;  // Instancia de tu subclase MyLoRaWanClass

void setup() {
  Serial.begin(115200);            // Inicializa la comunicación serial
  pinMode(RELAY_PIN, OUTPUT);      // Configura el relé como salida
  digitalWrite(RELAY_PIN, LOW);    // Apaga la bomba al inicio

  loraWan.displayJoining();         // Llamada de ejemplo a la subclase
}

void loop() {
  // Medir la distancia (nivel del agua)
  unsigned int distance = sonar.ping_cm();

  if (distance > 0) {
    Serial.print("Nivel de agua: ");
    Serial.print(distance);
    Serial.println(" cm");
  } else {
    Serial.println("Fuera de rango");
  }

  // Control de la bomba: si el nivel es inferior al umbral, enciende la bomba
  if (distance > WATER_THRESHOLD) {
    Serial.println("Bomba apagada (agua suficiente).");
    digitalWrite(RELAY_PIN, LOW);  // Apaga la bomba
  } else {
    Serial.println("Bomba encendida (nivel bajo de agua).");
    digitalWrite(RELAY_PIN, HIGH);  // Enciende la bomba
  }

  delay(1000);  // Espera 1 segundo antes de la próxima lectura
}
