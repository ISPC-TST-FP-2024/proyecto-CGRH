#include <Adafruit_Sensor.h>
#include <Adafruit_AHTX0.h>
#include <BluetoothSerial.h>

Adafruit_AHTX0 aht; // Crea una instancia del sensor AHT10
BluetoothSerial SerialBT; // Instancia del Bluetooth
bool requestData = false; // Variable para indicar si se solicita datos

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
  // Comprueba si hay datos disponibles para leer desde Bluetooth
  if (SerialBT.available()) {
    char command = SerialBT.read(); // Lee el comando

    // Si se recibe 'G', se solicita la lectura de datos
    if (command == 'G') {
      requestData = true; // Cambia la variable a true para solicitar datos
      SerialBT.println("Solicitando datos del sensor...");
    }
  }

  // Si se solicitó la lectura de datos
  if (requestData) {
    sensors_event_t humidity, temperature;
    aht.getEvent(&temperature, &humidity); // Lee los datos del sensor

    // Envía los datos por Bluetooth
    SerialBT.print(F("Temperatura: "));
    SerialBT.print(temperature.temperature);
    SerialBT.print(F(" °C, Humedad: "));
    SerialBT.print(humidity.relative_humidity);
    SerialBT.println(F(" %"));

    requestData = false; // Restablece la variable después de enviar los datos
  }

  delay(100); // Pequeña espera para evitar saturar el puerto serie
}
