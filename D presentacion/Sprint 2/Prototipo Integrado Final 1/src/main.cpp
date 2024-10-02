#include <Arduino.h>
#include "conexiones/wifi.h"
#include "conexiones/lora.h"
#include "conexiones/ble.h"
#include "sensores/sensor_aht10.h"
#include "sensores/sensor_bh1750.h"
#include "sensores/sensor_dht11.h"
#include "sensores/sensor_ldr.h"
#include "sensores/sensor_hcsr04.h"
#include "sensores/sensor_humedad_suelo.h"

void setup() {
  Serial.begin(115200);

  // Inicialización de conexiones
  iniciarWiFi();
  iniciarLoRa();
  iniciarBluetooth();

  // Inicialización de sensores
  iniciarAHT10();
  iniciarBH1750();
  iniciarDHT11();
  iniciarLDR();
  iniciarUltrasonico();
  iniciarHumedadSuelo();
}

void loop() {
  // Manejo de conexiones
  manejarWiFi();
  manejarLoRa();
  manejarBluetooth();

  // Lecturas de los sensores
  float temperaturaAHT10 = leerTemperaturaAHT10();
  float humedadAHT10 = leerHumedadAHT10();
  Serial.print("AHT10 - Temp: ");
  Serial.print(temperaturaAHT10);
  Serial.print(" °C, Humedad: ");
  Serial.println(humedadAHT10);

  float lux = leerLuxBH1750();
  Serial.print("BH1750 - Luz: ");
  Serial.print(lux);
  Serial.println(" lux");

  float temperaturaDHT11 = leerTemperaturaDHT11();
  float humedadDHT11 = leerHumedadDHT11();
  Serial.print("DHT11 - Temp: ");
  Serial.print(temperaturaDHT11);
  Serial.print(" °C, Humedad: ");
  Serial.println(humedadDHT11);

  int nivelLuzLDR = leerNivelLuzLDR();
  Serial.print("LDR - Nivel de luz: ");
  Serial.println(nivelLuzLDR);

  long distancia = leerDistanciaUltrasonico();
  Serial.print("HC-SR04 - Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  int humedadSuelo = leerHumedadSuelo();
  Serial.print("HL-69 - Humedad del suelo: ");
  Serial.println(humedadSuelo);

  delay(2000);  // Retraso entre lecturas
}
