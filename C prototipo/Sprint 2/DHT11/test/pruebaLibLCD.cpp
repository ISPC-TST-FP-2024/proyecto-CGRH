// Library version:1.1.5
// Example of picking custom I2C pins on ESP32

#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define I2C_SDA 21
#define I2C_SCL 22

LiquidCrystal_I2C lcd(0x27, 20, 4); // Configura el LCD: dirección 0x23, 20 columnas x 4 filas

void setup() {
  lcd.init(); // Inicializa el LCD
  lcd.backlight(); // Enciende la luz de fondo
}

void loop() {
  lcd.setCursor(0, 0); // Posicióna el cursor en la primera columna, primera línea
  lcd.print("Linea 1"); // Imprime el mensaje

  lcd.setCursor(0, 1); // Posicióna el cursor en la primera columna, segunda línea
  lcd.print("Linea 2"); // Imprime el mensaje

  lcd.setCursor(0, 2); // Posicióna el cursor en la primera columna, tercera línea
  lcd.print("Linea 3"); // Imprime el mensaje

  lcd.setCursor(0, 3); // Posicióna el cursor en la primera columna, cuarta línea
  lcd.print("Linea 4"); // Imprime el mensaje

  delay(2000); // Espera 2 segundos
  lcd.clear(); // Limpia el contenido del LCD
}