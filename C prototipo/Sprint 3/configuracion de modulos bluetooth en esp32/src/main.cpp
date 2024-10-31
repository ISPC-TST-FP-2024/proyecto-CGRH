#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <ST7735.h>
#include <Keypad.h> // Biblioteca del teclado

#define LED_PIN 2  // Pin donde está conectado el LED
#define PIN_LENGTH 4  // Longitud del PIN
char pairingPin[PIN_LENGTH + 1] = "1234";  // PIN de emparejamiento
bool bluetoothEnabled = false;
bool isPairingMode = false;

// Configuración del teclado
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {23, 22, 21, 19}; // Pines de fila
byte colPins[COLS] = {18, 5, 17, 16};  // Pines de columna
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

ST7735 _tft = ST7735(15, 4, 2);  // Inicialización de la pantalla

// Clase para manejar las conexiones de dispositivos
class MyServerCallbacks : public BLEServerCallbacks {
public:
    void onConnect(BLEServer* pServer) {
        Serial.println("Dispositivo conectado");
    }

    void onDisconnect(BLEServer* pServer) {
        Serial.println("Dispositivo desconectado");
    }
};

// Clase para manejar los errores de emparejamiento
class MySecurity : public BLESecurity {
protected:
    void onConfirmPIN(uint32_t remote_bda, const char* pin) override {
        if (strcmp(pin, pairingPin) == 0) {
            Serial.println("PIN correcto. Emparejamiento exitoso.");
            this->setPairingConfirmation(remote_bda);
        } else {
            Serial.println("PIN incorrecto. Emparejamiento fallido.");
            this->setPairingConfirmation(remote_bda);
        }
    }
};

// Clase para manejar los comandos recibidos
class MyCharacteristicCallbacks : public BLECharacteristicCallbacks {
public:
    void onWrite(BLECharacteristic* pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        if (value == "ON") {
            digitalWrite(LED_PIN, HIGH);  // Encender LED
            Serial.println("LED encendido");
            sendData("LED encendido");
        } else if (value == "OFF") {
            digitalWrite(LED_PIN, LOW);  // Apagar LED
            Serial.println("LED apagado");
            sendData("LED apagado");
        } else {
            Serial.println("Comando no reconocido");
        }
    }

    void sendData(const char* data) {
        Serial.print("Enviando datos: ");
        Serial.println(data);
    }
};

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    _tft.initR(INITR_BLACKTAB);
    _tft.fillScreen(ST77XX_BLACK);
    _tft.setTextColor(ST77XX_WHITE);
    _tft.setTextSize(2);
    _tft.setCursor(10, 10);
    initializeMenu();

    BLEDevice::init("ESP32_Device");
    MySecurity* security = new MySecurity();
    BLEServer* pServer = BLEDevice::createServer();
    pServer->setSecurity(security);
    pServer->setCallbacks(new MyServerCallbacks());

    BLEService *pService = pServer->createService(BLEUUID((uint16_t)0x181C));
    BLECharacteristic *pCharacteristic = pService->createCharacteristic(
        BLEUUID((uint16_t)0x2A6E),
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
    );

    pCharacteristic->setCallbacks(new MyCharacteristicCallbacks());
    pService->start();
    pServer->getAdvertising()->start();
    Serial.println("Esperando conexión...");
}

void loop() {
    handleMenuNavigation(); // Manejar la navegación del menú
}
