#include "lcdDisplay.h"

lcdDisplay::lcdDisplay() : lcd(0x27, 20, 2) {}

void lcdDisplay::init() {
    lcd.begin(20, 2, 0);
    lcd.backlight();
    lcd.clear();
    lcd.print("Esperando...");
}

void lcdDisplay::showMessage(String msg) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Recibido:");
    lcd.setCursor(0, 1);
    lcd.print(msg);
}
