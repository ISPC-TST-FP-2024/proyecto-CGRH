#include <WiFi.h>
#include "sensor.h"  // Incluir el archivo de cabecera

Sensor_DHT11 sensorDHT11(15, DHT11, 4, 1);   // Inicializar sensor (DHT11 en GPIO 15, WS2812 en GPIO 4)

void setup() {
    Serial.begin(115200);
    sensorDHT11.begin();  // Inicializar el sensor y el LED

}
void loop() {
    sensorDHT11.leerDatos();  // Leer datos del sensor
    sensorDHT11.actualizarLED();  // Actualizar el LED en función de la temperatura
    delay(2000);
}
