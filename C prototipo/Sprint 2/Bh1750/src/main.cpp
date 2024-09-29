// A falta del sensor BH1750, se utiliza en el modelo un foto resistor estandar que si esta preente en wokwi.
// Pero el codigo esta desarrollado para trabajar con el sensor indicado

#include <Wire.h>
#include <BH1750.h>

// Instancia del sensor BH1750
BH1750 lightMeter;

void setup() {
  // Inicializa la comunicación I2C en la ESP32
  Wire.begin(21, 22);  // SDA en el pin 21 y SCL en el pin 22 para ESP32
  
  // Inicializa el Monitor Serial
  Serial.begin(115200);
  Serial.println("Iniciando...");

  // Inicializa el sensor BH1750
  if (lightMeter.begin()) {
    Serial.println("Sensor BH1750 iniciado correctamente.");
  } else {
    Serial.println("Error al iniciar el sensor BH1750.");
    while (1);  // Si falla, queda en un bucle infinito
  }
}

void loop() {
  // Lee el nivel de luz en lux desde el sensor BH1750
  float lux = lightMeter.readLightLevel();
  
  // Muestra el valor de luz ambiente en el Monitor Serial
  Serial.print("Luz: ");
  Serial.print(lux);
  Serial.println(" lux");

  // Actualiza cada 1 segundo
  delay(1000);
}
