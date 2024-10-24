#ifndef BLE_LED_CONTROL_H
#define BLE_LED_CONTROL_H

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

class BLE_LED_Control {
private:
    int ledPin;  // Pin del LED
    std::string receivedValue;  // Valor recibido a través de BLE

public:
    BLECharacteristic *pCharacteristic;  // Característica BLE
    BLE_LED_Control(int pin);  // Constructor para inicializar el pin del LED
    void initBLE();  // Función para inicializar BLE
    void onWrite(BLECharacteristic *pCharacteristic);  // Callback para manejar los datos recibidos
};

#endif
