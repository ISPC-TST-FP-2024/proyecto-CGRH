#include "com_LoRa.h"

// Constructor que inicializa la frecuencia y los pines
com_LoRa::com_LoRa(long freq, int cs, int reset, int irq) 
    : frequency(freq), csPin(cs), resetPin(reset), irqPin(irq) {}

void com_LoRa::init() {
    // Configuración de los pines LoRa
    LoRa.setPins(csPin, resetPin, irqPin);
    
    // Inicialización del LoRa con la frecuencia especificada
    if (!LoRa.begin(frequency)) {
        Serial.println("Error al inicializar LoRa.");
        while (1);  // Bucle infinito si hay error
    }
    Serial.println("LoRa inicializado correctamente.");
}

void com_LoRa::configure(int sf, long bw, int cr) {
    LoRa.setSpreadingFactor(sf);   // Configurar el Spreading Factor
    LoRa.setSignalBandwidth(bw);   // Configurar el ancho de banda
    LoRa.setCodingRate4(cr);       // Configurar el Coding Rate
    Serial.println("LoRa configurado con parámetros avanzados.");
}

void com_LoRa::sendMessage(const String &msg) {
    LoRa.beginPacket();  // Iniciar paquete
    LoRa.print(msg);      // Escribir el mensaje
    LoRa.endPacket();     // Finalizar paquete
    Serial.println("Mensaje enviado: " + msg);
}

String com_LoRa::receiveMessage() {
    String message = "";
    int packetSize = LoRa.parsePacket();  // Verificar si hay un paquete disponible

    if (packetSize) {
        // Leer los datos disponibles
        while (LoRa.available()) {
            message += (char)LoRa.read();
        }
        Serial.println("Mensaje recibido: " + message);
    }

    return message;
}
