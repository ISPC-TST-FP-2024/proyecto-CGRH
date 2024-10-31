#ifndef MENU_H
#define MENU_H

#include <Arduino.h>

void toggleBluetooth();
void initializeMenu();
void handleMenuNavigation();
void enterPairingMode();

struct MenuOption {
    const char* title;
    void (*action)();
};

extern MenuOption mainMenu[];

#endif // MENU_H
