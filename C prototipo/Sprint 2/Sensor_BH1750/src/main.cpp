#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BH1750.h>
#include <ESP32_LoRaWAN.h> // Asegúrate de incluir la biblioteca si la necesitas

#define Vext 5 // Define el pin Vext

LiquidCrystal_I2C lcd(0x27, 16, 2);
BH1750 lightMeter;

void setup() {
    pinMode(Vext, OUTPUT); // Configura Vext como salida
    digitalWrite(Vext, HIGH); // Inicializa Vext a alto (cambia según tu lógica)

    Wire.begin();
    lcd.begin(16, 2);
    lcd.backlight();
    lightMeter.begin();
    lcd.setCursor(0, 0);
    lcd.print("Sensor de Luz");
}

void loop() {
    float lux = lightMeter.readLightLevel();
    lcd.setCursor(0, 1);
    lcd.print("Luz: ");
    lcd.print(lux);
    lcd.print(" lx   ");
    delay(1000);
}
