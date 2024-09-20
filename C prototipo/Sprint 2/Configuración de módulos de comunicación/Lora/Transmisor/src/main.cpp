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
  Serial.println("LoRa iniciado con éxito");
}

void loop() {
  Serial.println("Enviando mensaje...");
  LoRa.beginPacket();  // Inicia el paquete LoRa
  LoRa.print("Hola desde el Transmisor!");  // Mensaje que se va a transmitir
  LoRa.endPacket();    // Finaliza el paquete
  delay(5000);         // Esperar 5 segundos para la próxima transmisión
}
