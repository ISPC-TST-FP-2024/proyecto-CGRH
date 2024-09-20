#include "BluetoothSerial.h"  // Incluye la librería Bluetooth

BluetoothSerial SerialBT;  // crear el objeto Bluetooth

int ledPin = 2;  // pin donde esta conectado el LED

void setup() {
  Serial.begin(115200);  // Inicializa el monitor serie
  SerialBT.begin("ESP32_LED");  // Inicia Bluetooth con el nombre "ESP32_led"
  pinMode(ledPin, OUTPUT);  // Configurar el pin del LED como salida
  Serial.println("El dispositivo está listo para emparejarse.");
}

void loop() {
  if (SerialBT.available()) {  // Si hay datos disponibles desde el Bluetooth
    char caracter = SerialBT.read();  // Leer el caracter recibido
    Serial.print("Recibido vía Bluetooth: ");
    Serial.println(caracter);

    // Control del LED
    if (caracter == '1') {
      digitalWrite(ledPin, HIGH);  // prender el LED
      Serial.println("LED encendido");
    } else if (caracter == '0') {
      digitalWrite(ledPin, LOW);  // apagar el LED
      Serial.println("LED apagado");
    }
  }
}
