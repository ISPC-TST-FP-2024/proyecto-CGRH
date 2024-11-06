#include <Arduino.h>
#include "com_LoRa.h"
#include "lcdDisplay.h"

// Pines del módulo LoRa
#define CS_PIN 5
#define RESET_PIN 14
#define IRQ_PIN 2

// Instancia del módulo LoRa
com_LoRa lora(433E6, CS_PIN, RESET_PIN, IRQ_PIN);

lcdDisplay display;

volatile bool mensajeDisponible = false;

 
void IRAM_ATTR isrLoRa() {
    mensajeDisponible = true;  // Bandera para recibir mensaje
}

void setup() {
    Serial.begin(9600);
    while(!Serial);
    Wire.begin();
    display.init();
       // Inicializar LoRa
    lora.init();
    
    // Configuración avanzada (SF: 7, BW: 125 kHz, CR: 4/5)
    lora.configure(7, 125E3, 5);
    

    // Configura interrupción en DIO0
    attachInterrupt(digitalPinToInterrupt(2), isrLoRa, CHANGE);

    Serial.println("Receptor listo.");
    display.showMessage("Receptor escuchando");
}

void loop() {
    //display.showMessage("Receptor escuchando");
    if (mensajeDisponible) {
        mensajeDisponible = false;  // Reinicia bandera

        // Procesa el mensaje recibido
        String mensaje = lora.receiveMessage();
        if (mensaje != "") {
            Serial.println("Mensaje recibido: " + mensaje);
            display.showMessage(mensaje);  // Mostrar en LCD

            lora.sendMessage("ACK");
            Serial.println("ACK enviado.");
        }
    }
    delay(1000);
}
