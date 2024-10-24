#ifndef BLE_SERVER_H
#define BLE_SERVER_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <string>  // Incluir la librería estándar para std::string

class BLEServerHandler {
public:
    BLEServerHandler(const char* serviceUUID, const char* characteristicUUID);
    void initBLE();
    void setMessage(const std::string& msg);  // Cambiar a std::string
    std::string getMessage();                 // Cambiar a std::string

private:
    BLECharacteristic* pCharacteristic;
    const char* serviceUUID;
    const char* characteristicUUID;
};

#endif // BLE_SERVER_H
