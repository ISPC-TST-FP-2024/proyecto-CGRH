#include "BluetoothSerial.h"
#include "ble.h"

BluetoothSerial SerialBT;  // Objeto Bluetooth
int ledPin = 2;  // Pin del LED

void iniciarBle() {
  SerialBT.begin("ESP32_LED");
  pinMode(ledPin, OUTPUT);
  Serial.println("Bluetooth iniciado y listo para emparejar.");
}

void manejarBle() {
  if (SerialBT.available()) {
    char caracter = SerialBT.read();
    Serial.print("Recibido vía Bluetooth: ");
    Serial.println(caracter);

    // Control del LED
    if (caracter == '1') {
      digitalWrite(ledPin, HIGH);
      Serial.println("LED encendido");
    } else if (caracter == '0') {
      digitalWrite(ledPin, LOW);
      Serial.println("LED apagado");
    }
  }
}
