#include "BluetoothSerial.h"
#include <Preferences.h>  // Biblioteca para manejar NVS (memoria no volátil)

BluetoothSerial SerialBT;  // Objeto Bluetooth
Preferences preferences;
const char* PREF_BT_NAME = "bt_name";

String nombreDispositivo;
bool btGuardado = false;

// Función para pedir el nombre del dispositivo Bluetooth
void pedirNombreBLE() {
  Serial.println("Introduzca el nombre del dispositivo Bluetooth:");
  while (Serial.available() == 0);  // Espera por la entrada del usuario
  nombreDispositivo = Serial.readStringUntil('\n');  // Lee la entrada del nombre
}

// Función para guardar el nombre del dispositivo en NVS
void guardarNombreBLE() {
  preferences.begin("bluetooth", false);
  preferences.putString(PREF_BT_NAME, nombreDispositivo);
  preferences.end();
  Serial.println("Nombre Bluetooth guardado en memoria.");
}

void iniciarBle() {
  if (btGuardado) {
    nombreDispositivo = preferences.getString(PREF_BT_NAME, "ESP32");
  } else {
    pedirNombreBLE();  // Pide los datos si no están guardados
  }

  SerialBT.begin(nombreDispositivo.c_str());
  Serial.println("Bluetooth iniciado como: " + nombreDispositivo);

  // Pregunta si quiere guardar el nombre
  if (!btGuardado) {
    Serial.println("¿Desea guardar este dispositivo como predeterminado? (S/n)");
    while (Serial.available() == 0);  // Espera por la entrada
    char respuesta = Serial.read();
    if (respuesta == 'S' || respuesta == 's') {
      guardarNombreBLE();
      btGuardado = true;
    }
  }
}

void manejarBle() {
  if (SerialBT.available()) {
    char caracter = SerialBT.read();
    Serial.print("Recibido vía Bluetooth: ");
    Serial.println(caracter);

    // Control del LED (solo ejemplo)
    int ledPin = 2;  // Pin del LED
    pinMode(ledPin, OUTPUT);
    if (caracter == '1') {
      digitalWrite(ledPin, HIGH);
      Serial.println("LED encendido");
    } else if (caracter == '0') {
      digitalWrite(ledPin, LOW);
      Serial.println("LED apagado");
    }
  }
}

void setup() {
  Serial.begin(115200);
  
  // Inicializa la memoria no volátil
  preferences.begin("bluetooth", true);
  if (preferences.getString(PREF_BT_NAME, "") != "") {
    btGuardado = true;
  }
  preferences.end();
  
  iniciarBle();
}

void loop() {
  manejarBle();
}
