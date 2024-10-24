#include "ble_led_control.h"

// Definir los UUIDs
#define SERVICE_UUID "12345678-1234-1234-1234-123456789abc"
#define CHARACTERISTIC_UUID "87654321-4321-4321-4321-cba987654321"

// Constructor de la clase BLE_LED_Control
BLE_LED_Control::BLE_LED_Control(int pin) : ledPin(pin) {
    pinMode(ledPin, OUTPUT);  // Configurar el pin del LED como salida
}

// Función para inicializar BLE
void BLE_LED_Control::initBLE() {
    BLEDevice::init("ESP32_BLE");
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(SERVICE_UUID);

    // Crear la característica BLE
    pCharacteristic = pService->createCharacteristic(
                        CHARACTERISTIC_UUID,
                        BLECharacteristic::PROPERTY_READ |
                        BLECharacteristic::PROPERTY_WRITE
                    );

    pService->start();
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->start();
    Serial.println("BLE inicializado y listo para recibir comandos");
}

// Función que se llama cuando se escribe un valor en la característica BLE
void BLE_LED_Control::onWrite(BLECharacteristic *pCharacteristic) {
    receivedValue = pCharacteristic->getValue();  // Obtener el valor recibido
    
    if (receivedValue.length() > 0) {
        // Corregir la impresión del valor recibido
        Serial.println(("Valor recibido a través de BLE: " + receivedValue).c_str());

        // Control del LED según el valor recibido
        if (receivedValue == "ON") {
            digitalWrite(ledPin, HIGH);  // Encender el LED
            Serial.println("LED encendido");
        } else if (receivedValue == "OFF") {
            digitalWrite(ledPin, LOW);  // Apagar el LED
            Serial.println("LED apagado");
        }
    }
}
