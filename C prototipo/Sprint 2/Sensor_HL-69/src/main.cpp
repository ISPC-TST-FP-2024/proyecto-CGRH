#include <Arduino.h>
#include <Wire.h>  // Asegúrate de incluir Wire.h aquí
#include "SensorHumedadSuelo.h"
#include <LiquidCrystal_I2C.h> // Asegúrate de incluir esta biblioteca

// Define la dirección I2C y el tamaño de la pantalla
LiquidCrystal_I2C lcd(0x27, 16, 2); // Dirección I2C de tu LCD, ajusta según tu hardware

SensorHumedadSuelo sensorHumedadSuelo(36); // GPIO36

void setup() {
    Serial.begin(115200);
    sensorHumedadSuelo.begin();
    lcd.begin(16, 2); // Inicializa la pantalla LCD con 16 columnas y 2 filas
    lcd.backlight(); // Enciende la luz de fondo
}

void loop() {
    int humedad = sensorHumedadSuelo.readHumedad(); 
    Serial.print("Humedad del suelo: ");
    Serial.println(humedad);
    lcd.setCursor(0, 0); // Mueve el cursor a la primera línea
    lcd.print("Humedad: ");
    lcd.print(humedad); // Muestra la humedad en el LCD
    lcd.print(" %"); // Muestra el símbolo de porcentaje
    delay(2000);
}
