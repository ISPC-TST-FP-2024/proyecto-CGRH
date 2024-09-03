#include <Wire.h>
#include "LiquidCrystal_I2C.h"
#include "Teclado.h"
#include "Menu.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);  // Dirección I2C y tamaño del LCD
Teclado teclado(32, 33, 25, 26, 27, 14, 12);  // Pines del teclado
Menu menu(lcd, teclado);

void setup() {
    lcd.init();
    lcd.backlight();
    teclado.iniciar();
    menu.displayMenu();
}

void loop() {
    menu.navigate();  // Navega por el menú basado en la entrada del teclado
}