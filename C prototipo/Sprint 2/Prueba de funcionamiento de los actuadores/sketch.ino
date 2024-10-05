#include <ESP32Servo.h>

#define RELAY_PIN 26          // Pin del relé para la bomba de agua
#define LIGHT_PIN 27          // Pin del sistema de iluminación (LED)
#define SERVO_PIN 25          // Pin del motor de posicionamiento (servo)
#define MOISTURE_SENSOR_PIN 34 // Pin del sensor de humedad
#define MOISTURE_THRESHOLD 300 // Umbral de humedad

Servo motorServo;  // Declarar el servo para posicionamiento

void setup() {
  // Configuración del relé, LED y sensor
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LIGHT_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  // Inicialmente, la bomba de agua está apagada
  digitalWrite(LIGHT_PIN, LOW);  // Inicialmente, las luces están apagadas
  
  // Iniciar el servo
  motorServo.attach(SERVO_PIN);
  motorServo.write(0);  // Inicialmente el servo está en posición 0

  Serial.begin(115200);
  Serial.println("Iniciando el sistema de riego automático...");
}

void loop() {
  // Leer el valor del sensor de humedad
  int moistureValue = analogRead(MOISTURE_SENSOR_PIN);
  Serial.print("Humedad del suelo: ");
  Serial.println(moistureValue);

  // Controlar la bomba de agua
  if (moistureValue < MOISTURE_THRESHOLD) {
    Serial.println("Humedad baja, activando la bomba de agua...");
    digitalWrite(RELAY_PIN, HIGH);  // Activar bomba de agua
    motorServo.write(90);           // Mover el servo a 90 grados para posicionamiento
  } else {
    Serial.println("Humedad adecuada, desactivando la bomba de agua...");
    digitalWrite(RELAY_PIN, LOW);   // Desactivar bomba de agua
    motorServo.write(0);            // Retornar el servo a 0 grados
  }

  // Controlar el sistema de iluminación
  if (moistureValue > MOISTURE_THRESHOLD + 200) {
    Serial.println("Encendiendo el sistema de iluminación...");
    digitalWrite(LIGHT_PIN, HIGH);  // Encender luces
  } else {
    Serial.println("Apagando el sistema de iluminación...");
    digitalWrite(LIGHT_PIN, LOW);   // Apagar luces
  }

  delay(2000);  // Esperar 2 segundos antes de la siguiente lectura
}
