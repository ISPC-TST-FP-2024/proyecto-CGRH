#ifndef BLE_RECONNECT_H
#define BLE_RECONNECT_H

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

class BLE_Reconnect {
private:
    BLEServer* pServer;
    BLECharacteristic* pCharacteristic;
    bool deviceConnected;  // Cambiar acceso a privado
    bool oldDeviceConnected;

public:
    BLE_Reconnect();
    void initBLE();
    void notifyClients(const std::string& data);
    void checkConnection();

    // Funciones getter y setter para deviceConnected
    bool isDeviceConnected() const { return deviceConnected; }
    void setDeviceConnected(bool state) { deviceConnected = state; }

    // Getter y setter para oldDeviceConnected
    bool isOldDeviceConnected() const { return oldDeviceConnected; }
    void setOldDeviceConnected(bool state) { oldDeviceConnected = state; }
};

#endif
