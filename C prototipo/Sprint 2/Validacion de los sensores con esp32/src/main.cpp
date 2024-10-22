#include <Arduino.h>

const int pinHumedad = 34;  // GPIO34 - Humedad del suelo
const int pinPH = 35;       // GPIO36 - Sensor de pH
const int pinLluvia = 22;   // GPIO22 - Sensor de lluvia

void setup() {
  Serial.begin(115200);
  pinMode(pinLluvia, INPUT);
}

void loop() {
  int humedadValor = analogRead(pinHumedad);
  int phValor = analogRead(pinPH);
  int lluviaEstado = digitalRead(pinLluvia);

  Serial.print("Humedad del Suelo: ");
  Serial.println(humedadValor);
  Serial.print("Nivel de pH: ");
  Serial.println(phValor);
  Serial.print("Lluvia: ");
  Serial.println(lluviaEstado == LOW ? "Está lloviendo" : "No hay lluvia");

  delay(1000);
}
