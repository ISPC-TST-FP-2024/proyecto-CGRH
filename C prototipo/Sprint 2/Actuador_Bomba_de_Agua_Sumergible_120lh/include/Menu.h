#ifndef MENU_H
#define MENU_H

#include <LiquidCrystal_I2C.h>
#include "Teclado.h"

struct MenuOption {
    const char* title;
    void (*action)();  // Puntero a la función de acción del menú
};

class Menu {
public:
    Menu(LiquidCrystal_I2C& lcd, Teclado& teclado);
    void displayMenu();
    void navigate();
    void executeCurrentOption();

private:
    LiquidCrystal_I2C& _lcd;
    Teclado& _teclado;
    int _currentMenuIndex;
    int _currentMenuDepth;
};

#endif // MENU_H
