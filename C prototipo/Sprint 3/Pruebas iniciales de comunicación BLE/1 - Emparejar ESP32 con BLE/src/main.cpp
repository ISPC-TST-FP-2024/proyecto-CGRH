#include <Arduino.h>
#include "ble_server.h"

#define SERVICE_UUID        "12345678-1234-1234-1234-123456789abc"
#define CHARACTERISTIC_UUID "87654321-4321-4321-4321-abc987654321"

BLEServerHandler bleServer(SERVICE_UUID, CHARACTERISTIC_UUID);

void setup() {
    Serial.begin(115200);
    
    // Inicializar el servidor BLE
    bleServer.initBLE();
}

void loop() {
    // Ejemplo de uso: enviar un mensaje
    bleServer.setMessage("Hola, desde el ESP32");

    // Simular retraso entre envíos de mensajes
    delay(5000);
}
