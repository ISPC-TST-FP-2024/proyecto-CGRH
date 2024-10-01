#include <Arduino.h>
#include "conexiones/wifi.h"
#include "conexiones/lora.h"
#include "conexiones/ble.h"

void setup() {
  Serial.begin(115200);

  // Inicialización de conexiones
  iniciarWiFi();
  iniciarLoRa();
  iniciarBle();
}

void loop() {
  // Puedes usar condicionales o lógicas para diferentes tareas aquí.
  manejarWiFi();     // Manejamos la conexión y envío WiFi
  manejarLoRa();     // Manejamos la recepción y envío de LoRa
  manejarBle(); // Manejamos la comunicación vía Bluetooth
}
