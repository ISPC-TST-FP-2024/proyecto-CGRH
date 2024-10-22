/******************
A falta de un sensor de humedad disponible en wokwi, 
se utiliza a modo de ejemplo un potenciomentro

********************/ 


// Definir el pin ADC para el sensor de humedad (AOUT conectado a pin 34)
#define MOISTURE_SENSOR_PIN 34

void setup() {
  // Inicializar la comunicación serial
  Serial.begin(115200);
  
  // Configurar el pin del sensor como entrada
  pinMode(MOISTURE_SENSOR_PIN, INPUT);
}

void loop() {
  // Leer el valor analógico del sensor de humedad
  int sensorValue = analogRead(MOISTURE_SENSOR_PIN);
  
  // Convertir el valor en un porcentaje de humedad (0-100%)
  int moisturePercent = map(sensorValue, 0, 4095, 0, 100);
  
  // Mostrar el valor en el monitor serial
  Serial.print("Humedad del suelo: ");
  Serial.print(moisturePercent);
  Serial.println("%");

  // Añadir un retraso para las siguientes lecturas
  delay(1000);
}
