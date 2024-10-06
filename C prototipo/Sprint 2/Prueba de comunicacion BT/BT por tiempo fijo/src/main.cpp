#include <Adafruit_Sensor.h>
#include <Adafruit_AHTX0.h>
#include <BluetoothSerial.h>

Adafruit_AHTX0 aht; // Crea una instancia del sensor AHT10
BluetoothSerial SerialBT; // Instancia del Bluetooth

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT"); // Inicia el Bluetooth
  Serial.println("Bluetooth iniciado");

  if (!aht.begin()) { // Inicializa el sensor
    SerialBT.println("No se pudo encontrar el sensor AHT10");
    while (1) delay(10);
  }
  SerialBT.println("Sensor AHT10 iniciado.");
}

void loop() {
  sensors_event_t humidity, temperature;
  aht.getEvent(&temperature, &humidity); // Lee los datos del sensor

  // Envía los datos por Bluetooth
  SerialBT.print(F("Temperatura: "));
  SerialBT.print(temperature.temperature);
  SerialBT.print(F(" °C, Humedad: "));
  SerialBT.print(humidity.relative_humidity);
  SerialBT.println(F(" %"));

  delay(5000); // Espera 5 segundos antes de volver a leer
}
