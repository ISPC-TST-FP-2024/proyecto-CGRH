#include <SPI.h>
#include <LoRa.h>

const int ss = 18;    // Pin de NSS
const int rst = 14;   // Pin de RST
const int dio0 = 26;  // Pin de DIO0

void setup() {
  Serial.begin(115200);
  
  // Inicializar LoRa
  LoRa.setPins(ss, rst, dio0);
  if (!LoRa.begin(433E6)) {  // Frecuencia de 433 MHz
    Serial.println("Error al iniciar LoRa");
    while (1);
  }
  Serial.println("Receptor LoRa listo");
}

void loop() {
  // Verificar si se recibió algún paquete
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.print("Paquete recibido: ");
    while (LoRa.available()) {
      String received = LoRa.readString();
      Serial.println(received);
    }
  }
}
