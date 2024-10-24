#include "ble_ajuste_parametros.h"
#include "Arduino.h"

void MyServerCallbacks::onConnect(BLEServer* server) {
    instance->setDispositivoConectado(true); // Usar el setter
    Serial.println("Dispositivo conectado.");
}

void MyServerCallbacks::onDisconnect(BLEServer* server) {
    instance->setDispositivoConectado(false); // Usar el setter
    Serial.println("Dispositivo desconectado.");

    // Iniciar nuevamente la publicidad para permitir la reconexión
    server->startAdvertising();
    Serial.println("Esperando reconexión...");
}


BLE_AjusteParametros::BLE_AjusteParametros() : servidorBLE(nullptr), caracteristicaBLE(nullptr), dispositivoConectado(false) {}

void BLE_AjusteParametros::iniciarBLE() {
    BLEDevice::init("ESP32 Ajuste BLE");
    servidorBLE = BLEDevice::createServer();
    servidorBLE->setCallbacks(new MyServerCallbacks(this));

    BLEService* servicioBLE = servidorBLE->createService(BLEUUID((uint16_t)0x180F));
    caracteristicaBLE = servicioBLE->createCharacteristic(
        BLEUUID((uint16_t)0x2A19),
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
    );

    servicioBLE->start();
    servidorBLE->getAdvertising()->start();
    Serial.println("Esperando conexión...");
}

void BLE_AjusteParametros::notificarClientes(const std::string& mensaje) {
    if (isDispositivoConectado()) {
        caracteristicaBLE->setValue(mensaje);
        caracteristicaBLE->notify();
        Serial.println(mensaje.c_str());  // Convertir std::string a const char* para Serial.println
    }
}


void BLE_AjusteParametros::verificarConexion() {
    if (!isDispositivoConectado()) {
        delay(500); // Dar tiempo para la reconexión
        servidorBLE->startAdvertising(); // Reiniciar la publicidad para reconectar
        Serial.println("Esperando reconexión...");
    }
}

void BLE_AjusteParametros::ajustarParametrosPublicidad(uint32_t intervalo) {
    servidorBLE->getAdvertising()->setMinInterval(intervalo / 0.625); // Convertir ms a intervalo BLE
    servidorBLE->getAdvertising()->setMaxInterval(intervalo / 0.625);
    servidorBLE->getAdvertising()->start();
    Serial.println("Parámetros de publicidad ajustados.");
}

void BLE_AjusteParametros::ajustarParametrosConexion(uint16_t intervaloMinimo, uint16_t intervaloMaximo, uint16_t latencia, uint16_t tiempoEspera) {
    // Aquí puedes ajustar los parámetros de conexión BLE (si es necesario).
    Serial.println("Parámetros de conexión ajustados.");
}
