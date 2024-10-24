#include <Arduino.h>

#include "ble_led_control.h"

// Crear una instancia de la clase BLE_LED_Control
BLE_LED_Control ledControl(2);  // Usar el pin 2 para el LED

class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    ledControl.onWrite(pCharacteristic);  // Pasar el control a la clase BLE_LED_Control
  }
};

void setup() {
    Serial.begin(115200);

    // Inicializar BLE
    ledControl.initBLE();
    
    // Asignar las callbacks
    ledControl.pCharacteristic->setCallbacks(new MyCallbacks());
}

void loop() {
    // No se necesita hacer nada aquí, el control BLE se maneja mediante callbacks
}
