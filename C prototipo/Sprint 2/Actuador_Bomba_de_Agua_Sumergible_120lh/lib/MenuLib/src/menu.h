#ifndef MENU_H
#define MENU_H

#include "LiquidCrystal_I2C.h"
#include "Teclado.h"

// Estructura para definir las opciones del menú
struct MenuOption {
    const char* title;
    void (*action)();  // Puntero a función para ejecutar la opción
};

// Declaración de la clase Menu
class Menu {
public:
    Menu(LiquidCrystal_I2C& lcd, Teclado& teclado);
    void displayMenu();  // Muestra el menú en la pantalla LCD
    void navigate();     // Maneja la navegación por el menú

private:
    LiquidCrystal_I2C& _lcd;
    Teclado& _teclado;
    int _currentMenuIndex;  // Índice de la opción de menú seleccionada
    int _currentMenuDepth;  // Nivel de profundidad en el menú

    void updateDisplay();  // Actualiza la pantalla LCD según la opción seleccionada
    void executeCurrentOption();  // Ejecuta la acción de la opción seleccionada
};

#endif
