#include <SPI.h>
#include <LoRa.h>
#include "lora.h"

const int ss = 18;
const int rst = 14;
const int dio0 = 26;

void iniciarLoRa() {
  LoRa.setPins(ss, rst, dio0);
  if (!LoRa.begin(433E6)) {
    Serial.println("Error al iniciar LoRa");
    while (1);
  }
  Serial.println("LoRa iniciado con éxito");
}

void manejarLoRa() {
  // Ejemplo de transmisión
  Serial.println("Enviando mensaje...");
  LoRa.beginPacket();
  LoRa.print("Hola desde el Transmisor!");
  LoRa.endPacket();

  // Ejemplo de recepción
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.print("Paquete recibido: ");
    while (LoRa.available()) {
      String recibido = LoRa.readString();
      Serial.println(recibido);
    }
  }

  delay(5000); // Esperar 5 segundos antes de la siguiente operación
}
