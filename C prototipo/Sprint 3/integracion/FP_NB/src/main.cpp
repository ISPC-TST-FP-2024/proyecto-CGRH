#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>  // para el sensor AHT10
#include <BluetoothSerial.h>  // librería para Bluetooth
#include <esp_system.h>  // para generar el id único
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

// definir variables para el sensor de humedad
const int pinHumResistivo = 34; // humedad resistiva (parte superior)
const int pinHumCapacitivo = 35; // humedad capacitiva (parte inferior)

// definir pines para otros sensores
const int pinLdr = 32; // sensor de luz
const int pinUltrasonicoTrigger = 13; // trigger ultrasonico
const int pinUltrasonicoEcho = 12; // echo ultrasonico

// definir para Bluetooth y pantalla
BluetoothSerial SerialBT;
Adafruit_AHTX0 aht; // sensor de temperatura y humedad
Adafruit_ST7735 tft = Adafruit_ST7735(5, 18, 19); // pantalla SPI

// variables para la lógica
String nodoID = "NODO2_BT"; // id único para este nodo
int nivelAgua = 0; // inicializar nivel de agua
float temp = 0.0, hum = 0.0; // variables para temperatura y humedad

// función para medir nivel de agua con sensor ultrasónico
int medirNivelAgua() {
  long duracion;
  digitalWrite(pinUltrasonicoTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pinUltrasonicoTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinUltrasonicoTrigger, LOW);
  
  duracion = pulseIn(pinUltrasonicoEcho, HIGH);
  int distancia = duracion * 0.034 / 2;
  
  return distancia;
}

// setup inicial
void setup() {
  Serial.begin(115200); // para debug
  SerialBT.begin("Nodo2_Cultivo"); // inicializar Bluetooth
  Wire.begin(); // iniciar i2c para el sensor AHT10
  aht.begin(); // iniciar AHT10
  pinMode(pinHumResistivo, INPUT);
  pinMode(pinHumCapacitivo, INPUT);
  pinMode(pinLdr, INPUT);
  pinMode(pinUltrasonicoTrigger, OUTPUT);
  pinMode(pinUltrasonicoEcho, INPUT);
  
  // iniciar pantalla
  tft.initR(INITR_144GREENTAB);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextWrap(true);
  tft.setTextSize(1);
  
  tft.println("Nodo 2 BT");
}

// loop principal
void loop() {
  // leer sensores de temperatura y humedad
  sensors_event_t tempEvent, humEvent;
  aht.getEvent(&humEvent, &tempEvent);
  temp = tempEvent.temperature;  // obtener temp
  hum = humEvent.relative_humidity;  // obtener humedad
  
  // leer humedad del suelo
  int humedadSueloResistivo = analogRead(pinHumResistivo);
  int humedadSueloCapacitivo = analogRead(pinHumCapacitivo);
  
  // leer luz ambiental
  int luz = analogRead(pinLdr);
  
  // medir nivel de agua
  nivelAgua = medirNivelAgua();

  // mostrar datos en pantalla
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.printf("Temp: %.1fC\nHum: %.1f%%\nLuz: %d\nHum Suelo (Resistivo): %d\nHum Suelo (Capacitivo): %d\nNivel Agua: %d\n", temp, hum, luz, humedadSueloResistivo, humedadSueloCapacitivo, nivelAgua);
  
  // generar mensaje para enviar por bluetooth
  String mensaje = nodoID + ";Temp:" + String(temp) + ";Hum:" + String(hum) + ";Luz:" + String(luz) + ";HumRes:" + String(humedadSueloResistivo) + ";HumCap:" + String(humedadSueloCapacitivo) + ";NivelAgua:" + String(nivelAgua);
  
  // enviar por bluetooth
  SerialBT.println(mensaje);
  
  // esperar un poco antes de repetir
  delay(5000);
}
