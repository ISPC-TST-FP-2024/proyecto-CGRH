#include <Arduino.h>
#include "ble_reconnect.h"

BLE_Reconnect bleModule;

void setup() {
    Serial.begin(115200);
    bleModule.initBLE();
}

void loop() {
    bleModule.checkConnection();

    // Ejemplo de uso: enviar notificación si el dispositivo está conectado
    if (bleModule.isDeviceConnected()) {
        bleModule.notifyClients("Mensaje desde ESP32");
    }

    delay(1000);
}
