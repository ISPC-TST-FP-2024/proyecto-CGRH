#include <SPI.h>
#include <LoRa.h>
#include "lora.h"

// Pines de LoRa
const int ss = 18;
const int rst = 14;
const int dio0 = 26;

// Parámetros de LoRa
const long frecuencia = 433E6;          // Frecuencia (ajusta según tu región)
const int sf = 7;                       // Spreading Factor (ajusta entre 7-12, mayor valor = mayor rango pero más lento)
const long bandwidth = 125E3;           // Ancho de banda (puede ser 125E3, 250E3, 500E3)
const int txPower = 14;                 // Potencia de transmisión en dB (máximo 20 para la mayoría de módulos)
const int preambleLength = 8;           // Longitud del preámbulo (incrementar si necesitas mejorar la detección)

// Función para iniciar LoRa
void iniciarLoRa() {
  LoRa.setPins(ss, rst, dio0);

  // Iniciar LoRa
  if (!LoRa.begin(frecuencia)) {
    Serial.println("Error al iniciar LoRa. Verifique la conexión.");
    while (1);  // Detiene el programa si LoRa no inicia
  }

  // Configuraciones adicionales de LoRa
  LoRa.setSpreadingFactor(sf);              // Ajustar factor de difusión
  LoRa.setSignalBandwidth(bandwidth);       // Ajustar ancho de banda
  LoRa.setTxPower(txPower);                 // Ajustar potencia de transmisión
  LoRa.setPreambleLength(preambleLength);   // Ajustar longitud de preámbulo

  Serial.println("LoRa iniciado con éxito en frecuencia de 433 MHz");
}

// Función para manejar el envío y recepción de datos LoRa
void manejarLoRa() {
  // Transmisión de datos
  enviarMensajeLoRa("Hola desde el transmisor!");

  // Recepción de datos con timeout
  recibirMensajeLoRa();
  
  // Añadir un pequeño retraso entre transmisiones
  delay(10000); // Espera 10 segundos antes de la siguiente operación
}

// Función para enviar mensajes LoRa
void enviarMensajeLoRa(String mensaje) {
  Serial.println("Enviando mensaje...");

  LoRa.beginPacket();           // Comienza el paquete
  LoRa.print(mensaje);          // Escribe el mensaje en el paquete
  LoRa.endPacket();             // Finaliza y envía el paquete
  
  Serial.println("Mensaje enviado: " + mensaje);
}

// Función para recibir mensajes LoRa con timeout
void recibirMensajeLoRa() {
  int packetSize = LoRa.parsePacket();  // Analiza si se ha recibido un paquete

  if (packetSize > 0) {
    Serial.print("Paquete recibido: ");
    
    String recibido = "";                // String para almacenar los datos recibidos
    while (LoRa.available()) {
      recibido += (char)LoRa.read();     // Leer los datos disponibles
    }

    Serial.println(recibido);            // Imprime el mensaje recibido

    // Verificar CRC
    if (LoRa.packetRssi() < -120 || LoRa.packetSnr() < -20) {
      Serial.println("Advertencia: Posible problema de señal o datos corruptos.");
    }
  }
}

// Configuración inicial de Arduino
void setup() {
  Serial.begin(115200);        // Iniciar comunicación serie para debug
  iniciarLoRa();               // Iniciar LoRa con configuraciones
}

// Bucle principal
void loop() {
  manejarLoRa();               // Manejar transmisión y recepción de LoRa
}
