#ifndef MENU_H
#define MENU_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "Teclado.h"

// Estructura para definir las opciones del menú
struct MenuOption {
    const char* title;
    void (*action)();  // Puntero a función para ejecutar la opción
};

// Declaración de la clase Menu
class Menu {
public:
    Menu(Adafruit_ST7735& tft, Teclado& teclado);
    void displayMenu();  // Muestra el menú en la pantalla
    void navigate();     // Maneja la navegación por el menú

private:
    Adafruit_ST7735& _tft; // Cambia LiquidCrystal_I2C por Adafruit_ST7735
    Teclado& _teclado;
    int _currentMenuIndex;  // Índice de la opción de menú seleccionada
    int _currentMenuDepth;  // Nivel de profundidad en el menú

    void updateDisplay();  // Actualiza la pantalla según la opción seleccionada
    void executeCurrentOption();  // Ejecuta la acción de la opción seleccionada
};

#endif
