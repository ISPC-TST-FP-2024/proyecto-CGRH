#include "Menu.h"
#include "Teclado.h"

// Constructor del menú
Menu::Menu(LiquidCrystal_I2C& lcd, Teclado& teclado) 
  : _lcd(lcd), _teclado(teclado), _currentMenuIndex(0), _currentMenuDepth(0) {}

// Opciones del menú principal
MenuOption mainMenu[] = {
    {"1. Configuracion", nullptr},
    {"2. Sensores", nullptr},
    {"3. Actuadores", nullptr},
    {"4. Visualizacion", nullptr},
    {"5. Red", nullptr},
    {"6. Supervision", nullptr},
    {"7. Sistema", nullptr}
};

const int mainMenuSize = sizeof(mainMenu) / sizeof(MenuOption);

// Muestra el menú en la pantalla LCD
void Menu::displayMenu() {
    _lcd.clear();
    _lcd.setCursor(0, 0);
    _lcd.print(mainMenu[_currentMenuIndex].title);
}

// Navega por el menú basado en la entrada del teclado
void Menu::navigate() {
    char key = _teclado.leerTecla();

    if (key == '2') {  // Flecha arriba
        _currentMenuIndex = (_currentMenuIndex - 1 + mainMenuSize) % mainMenuSize;
        displayMenu();
    } 
    else if (key == '8') {  // Flecha abajo
        _currentMenuIndex = (_currentMenuIndex + 1) % mainMenuSize;
        displayMenu();
    } 
    else if (key == '*') {  // Enter
        executeCurrentOption();
    } 
    else if (key == '#') {  // Escape
        _lcd.clear();
        _lcd.print("Saliendo...");
        delay(1000);
    }
}

// Ejecuta la opción del menú seleccionada
void Menu::executeCurrentOption() {
    if (mainMenu[_currentMenuIndex].action != nullptr) {
        mainMenu[_currentMenuIndex].action();
    }
    else {
        _lcd.clear();
        _lcd.print("Opcion no disponible");
        delay(1000);
        displayMenu();
    }
}
