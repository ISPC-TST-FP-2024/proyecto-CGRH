#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
float sensorValue = 25.5;  // Valor de ejemplo del sensor

// UUIDs para el servicio y la característica
#define SERVICE_UUID        "12345678-1234-1234-1234-123456789012"
#define CHARACTERISTIC_UUID "87654321-4321-4321-4321-210987654321"

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
  }

  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
  }
};

class MyCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        if (value.length() > 0) {
            Serial.println("Recibido desde Cliente:");
            for (int i = 0; i < value.length(); i++) {
                Serial.print(value[i]);
            }
            Serial.println();
        }
    }
};

void setup() {
  Serial.begin(115200);

  // Inicializar dispositivo BLE
  BLEDevice::init("ESP32_BLE");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Crear el servicio BLE
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Crear la característica BLE
  pCharacteristic = pService->createCharacteristic(
                     CHARACTERISTIC_UUID,
                     BLECharacteristic::PROPERTY_READ |
                     BLECharacteristic::PROPERTY_WRITE |
                     BLECharacteristic::PROPERTY_NOTIFY
                   );

  pCharacteristic->setCallbacks(new MyCallbacks());  // Manejar las escrituras
  pCharacteristic->addDescriptor(new BLE2902());

  // Iniciar el servicio BLE
  pService->start();

  // Comenzar a anunciar el dispositivo BLE
  pServer->getAdvertising()->start();
  Serial.println("Esperando conexión BLE...");
}

void loop() {
  if (deviceConnected) {
    // Simular el envío de datos del sensor (temperatura)
    sensorValue += 0.1;
    pCharacteristic->setValue(sensorValue);
    pCharacteristic->notify();  // Notificar al cliente
    Serial.print("Enviando datos: ");
    Serial.println(sensorValue);
    delay(1000);
  }
}
