#include <Arduino.h>
#include "MoistureSensor.h"  // Asegúrate de incluir el archivo de encabezado

#define MOISTURE_SENSOR_PIN 34

MoistureSensor moistureSensor(MOISTURE_SENSOR_PIN); // Crear instancia del sensor

void setup() {
  Serial.begin(115200);
  moistureSensor.begin();  // Inicializa el sensor
}

void loop() {
  int moisturePercent = moistureSensor.readMoisture(); // Lee la humedad
  Serial.print("Humedad del suelo: ");
  Serial.print(moisturePercent);
  Serial.println("%");
  delay(1000);  // Añadir un retraso para las siguientes lecturas
}
