#include "menu.h"
#include <BLEDevice.h>
#include <ST7735.h>
#include <Keypad.h>

extern ST7735 _tft;
extern bool bluetoothEnabled;
extern bool isPairingMode;

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

MenuOption mainMenu[] = {
    {"1. Configuracion", nullptr},
    {"2. Sensores", nullptr},
    {"3. Actuadores", nullptr},
    {"4. Visualizacion", nullptr},
    {"5. Red", nullptr},
    {"6. Supervision", nullptr},
    {"7. Sistema", nullptr},
    {"8. Bluetooth", toggleBluetooth},
    {"9. Emparejar", enterPairingMode}
};

void initializeMenu() {
    _tft.fillScreen(ST77XX_BLACK);
    _tft.println("Menu Inicial");
}

void toggleBluetooth() {
    if (bluetoothEnabled) {
        BLEDevice::deinit(false);
        Serial.println("Bluetooth desactivado");
        bluetoothEnabled = false;
    } else {
        BLEDevice::init("ESP32_Device");
        Serial.println("Bluetooth activado");
        bluetoothEnabled = true;
    }
    displayMenu();
}

void enterPairingMode() {
    isPairingMode = true;
    Serial.println("Modo de emparejamiento activado. Introduzca el PIN en el dispositivo que se está emparejando.");
    displayMenu();
}

void displayMenu() {
    _tft.fillScreen(ST77XX_BLACK);
    _tft.setTextColor(ST77XX_WHITE);
    _tft.setTextSize(2);
    _tft.setCursor(10, 10);

    String status = bluetoothEnabled ? "Bluetooth ON" : "Bluetooth OFF";
    _tft.println(status);

    for (int i = 0; i < sizeof(mainMenu) / sizeof(mainMenu[0]); i++) {
        _tft.println(mainMenu[i].title);
    }
}

void handleMenuNavigation() {
    char key = keypad.getKey(); // Lee la tecla presionada

    if (key) { // Si se ha presionado una tecla
        switch (key) {
            case '1':
                mainMenu[0].action(); // Llama a la acción de la opción 1
                break;
            case '2':
                mainMenu[1].action(); // Llama a la acción de la opción 2
                break;
            case '3':
                mainMenu[2].action(); // Llama a la acción de la opción 3
                break;
            case '4':
                mainMenu[3].action(); // Llama a la acción de la opción 4
                break;
            case '5':
                mainMenu[4].action(); // Llama a la acción de la opción 5
                break;
            case '6':
                mainMenu[5].action(); // Llama a la acción de la opción 6
                break;
            case '7':
                mainMenu[6].action(); // Llama a la acción de la opción 7
                break;
            case '8':
                toggleBluetooth(); // Alterna Bluetooth
                break;
            case '9':
                enterPairingMode(); // Entra en modo de emparejamiento
                break;
            default:
                Serial.println("Tecla no reconocida");
                break;
        }
    }
}
