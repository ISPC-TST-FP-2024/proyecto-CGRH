#ifndef COM_LORA_H
#define COM_LORA_H

#include <SPI.h>
#include <LoRa.h>  // Librería para manejar LoRa

class com_LoRa {
private:
    long frequency;  // Frecuencia del módulo LoRa
    int csPin, resetPin, irqPin;  // Pines para el módulo LoRa

public:
    com_LoRa(long freq, int cs, int reset, int irq);  // Constructor
    void init();              // Inicializar LoRa
    void configure(int sf, long bw, int cr);  // Configuración avanzada
    void sendMessage(const String &msg);  // Enviar mensaje
    String receiveMessage();  // Recibir mensaje
};

#endif
