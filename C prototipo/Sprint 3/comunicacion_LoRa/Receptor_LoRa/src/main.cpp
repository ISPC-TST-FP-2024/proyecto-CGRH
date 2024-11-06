#include <Arduino.h>

#include "lcdDisplay.h"

#include <SPI.h>
#include <LoRa.h>

lcdDisplay pantalla;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Wire.begin();
  pantalla.init();

  Serial.println("LoRa Receiver");

  LoRa.setPins(5, 14, 2);
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("Lora iniciado");
}

void loop() {
  String mensaje;
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      mensaje += (char)LoRa.read();
      Serial.print(mensaje);
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
    LoRa.beginPacket();  // Iniciar paquete
    LoRa.print("ACK");      // Escribir el mensaje
    LoRa.endPacket();     // Finalizar paquete
    Serial.println("ACK enviado: ");
    pantalla.showMessage(mensaje);
  }
}