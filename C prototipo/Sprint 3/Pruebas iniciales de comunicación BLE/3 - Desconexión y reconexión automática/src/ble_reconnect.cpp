#include "ble_reconnect.h"
#include "Arduino.h"
// Definir las callbacks directamente dentro de la clase BLEServerCallbacks
class MyServerCallbacks : public BLEServerCallbacks {
    BLE_Reconnect* bleModule; // Instancia de BLE_Reconnect para acceder a deviceConnected

public:
    MyServerCallbacks(BLE_Reconnect* module) : bleModule(module) {}

    void onConnect(BLEServer* pServer) override {
        bleModule->setDeviceConnected(true);
        Serial.println("Dispositivo conectado.");
    }

    void onDisconnect(BLEServer* pServer) override {
        bleModule->setDeviceConnected(false);
        Serial.println("Dispositivo desconectado.");
    }
};

BLE_Reconnect::BLE_Reconnect() : pServer(nullptr), pCharacteristic(nullptr), deviceConnected(false), oldDeviceConnected(false) {}

void BLE_Reconnect::initBLE() {
    BLEDevice::init("ESP32 BLE Reconnect");

    // Crear el servidor BLE
    pServer = BLEDevice::createServer();

    // Establecer las callbacks, pasando la instancia actual de BLE_Reconnect
    pServer->setCallbacks(new MyServerCallbacks(this));

    // Crear el servicio y la característica BLE
    BLEService* pService = pServer->createService(BLEUUID((uint16_t)0x180F));

    pCharacteristic = pService->createCharacteristic(
        BLEUUID((uint16_t)0x2A19),
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
    );

    pService->start();
    pServer->getAdvertising()->start();
    Serial.println("Esperando conexión...");

    // Inicializar el estado anterior de conexión
    setOldDeviceConnected(isDeviceConnected());
}

void BLE_Reconnect::notifyClients(const std::string& data) {
    if (isDeviceConnected()) {
        pCharacteristic->setValue(data);
        pCharacteristic->notify();
    }
}

void BLE_Reconnect::checkConnection() {
    // Si el dispositivo se desconecta
    if (!isDeviceConnected() && isOldDeviceConnected()) {
        delay(500); // Dar tiempo para la reconexión
        pServer->startAdvertising(); // Reiniciar la publicidad
        Serial.println("Esperando reconexión...");
        setOldDeviceConnected(isDeviceConnected());
    }

    // Si el dispositivo se conecta nuevamente
    if (isDeviceConnected() && !isOldDeviceConnected()) {
        setOldDeviceConnected(isDeviceConnected());
    }
}
