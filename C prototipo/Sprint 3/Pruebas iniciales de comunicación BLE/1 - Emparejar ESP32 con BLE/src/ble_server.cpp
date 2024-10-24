#include <Arduino.h>  // Asegúrate de incluir esta librería

#include "ble_server.h"

BLEServerHandler::BLEServerHandler(const char* serviceUUID, const char* characteristicUUID)
    : serviceUUID(serviceUUID), characteristicUUID(characteristicUUID) {}

void BLEServerHandler::initBLE() {
    BLEDevice::init("ESP32 BLE Server");
    BLEServer *pServer = BLEDevice::createServer();
    
    BLEService *pService = pServer->createService(BLEUUID(serviceUUID));
    pCharacteristic = pService->createCharacteristic(
                          BLEUUID(characteristicUUID),
                          BLECharacteristic::PROPERTY_READ | 
                          BLECharacteristic::PROPERTY_WRITE);
    
    pService->start();
    
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(BLEUUID(serviceUUID));
    pAdvertising->setScanResponse(true);
    pAdvertising->start();
    
    Serial.println("Servidor BLE iniciado y anunciando");  // Mensaje de inicialización
}

void BLEServerHandler::setMessage(const std::string& msg) {
    pCharacteristic->setValue(msg);
    pCharacteristic->notify();
    Serial.println("Mensaje enviado: " + String(msg.c_str()));  // Imprime el mensaje
}

std::string BLEServerHandler::getMessage() {
    return pCharacteristic->getValue();
}
