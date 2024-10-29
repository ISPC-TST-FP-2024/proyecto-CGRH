#include "MyLoRa.h"
#include <Arduino.h>
#include "Vextpin.h"

MyLoRaClass::MyLoRaClass() {
    pinMode(VextPin, OUTPUT); // Configura el pin como salida
}

void MyLoRaClass::displayJoining() {
    Serial.println("Joining...");
    digitalWrite(VextPin, LOW); // Configura el pin VextPin bajo
}

void MyLoRaClass::displayJoined() {
    Serial.println("Joined!");
    digitalWrite(VextPin, LOW); // Mantén el pin VextPin bajo
}

void MyLoRaClass::displaySending() {
    Serial.println("Sending...");
    digitalWrite(VextPin, LOW); // Configura el pin VextPin bajo
}

void MyLoRaClass::displayAck() {
    Serial.println("Acknowledgment received");
    digitalWrite(VextPin, HIGH); // Configura el pin VextPin alto
}
