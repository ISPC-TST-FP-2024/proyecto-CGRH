#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BH1750.h>
#include <ESP32_LoRaWAN.h>
#include "Menu.h"
#include "Teclado.h"

#define Vext 5 // Define el pin Vext

LiquidCrystal_I2C lcd(0x27, 16, 2);
BH1750 lightMeter;
Teclado teclado;
Menu menu(lcd, teclado);

void setup() {
    pinMode(Vext, OUTPUT);
    digitalWrite(Vext, HIGH); // Inicializa Vext a alto

    Wire.begin();
    lcd.begin(16, 2);
    lcd.backlight();
    lightMeter.begin();
    
    lcd.setCursor(0, 0);
    lcd.print("Sensor de Luz");
    delay(1000);

    menu.displayMenu(); // Muestra el menú inicial
}

void loop() {
    // Muestra el nivel de luz y navega por el menú
    float lux = lightMeter.readLightLevel();
    lcd.setCursor(0, 1);
    lcd.print("Luz: ");
    lcd.print(lux);
    lcd.print(" lx   ");
    
    menu.navigate(); // Detecta las teclas presionadas y navega el menú
    delay(1000);
}
