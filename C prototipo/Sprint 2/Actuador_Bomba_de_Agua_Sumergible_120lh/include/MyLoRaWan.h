#ifndef MY_LORAWAN_H
#define MY_LORAWAN_H

#include <ESP32_LoRaWAN.h>
#include "Vextpin.h"

#define VextPin 21 // Cambiamos Vext a VextPin

class MyLoRaWanClass : public LoRaWanClass {
public:
    MyLoRaWanClass() : LoRaWanClass() {
        pinMode(VextPin, OUTPUT); // Configura el pin como salida
    }

    void displayJoining() {
        digitalWrite(VextPin, LOW); // Asegúrate de que VextPin está bajo
        Serial.println("Joining to LoRa network...");
    }

    void displayJoined() {
        digitalWrite(VextPin, HIGH); // Asegúrate de que VextPin está alto
        Serial.println("Joined LoRa network!");
    }

    void displaySending() {
        digitalWrite(VextPin, LOW); // Asegúrate de que VextPin está bajo
        Serial.println("Sending data...");
    }

    void displayAck() {
        digitalWrite(VextPin, HIGH); // Asegúrate de que VextPin está alto
        Serial.println("Acknowledgment received!");
    }
};

#endif // MY_LORAWAN_H
