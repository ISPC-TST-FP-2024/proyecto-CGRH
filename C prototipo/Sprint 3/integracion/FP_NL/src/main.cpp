#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>  // sensor AHT10 para temperatura y humedad
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>  // pantalla SPI

// definir variables para los pines de los sensores
const int pinHumResistivo = 34; // humedad resistiva (parte superior)
const int pinHumCapacitivo = 35; // humedad capacitiva (parte inferior)
const int pinLdr = 32; // sensor de luz
const int pinUltrasonicoTrigger = 13; // trigger ultrasónico
const int pinUltrasonicoEcho = 12; // echo ultrasónico

// configuración LoRa
#define SS 18    // seleccionar pin LoRa
#define RST 14   // pin de reset LoRa
#define DIO0 26  // pin DIO0 LoRa

// configuración pantalla SPI
Adafruit_AHTX0 aht;  // sensor AHT10
Adafruit_ST7735 tft = Adafruit_ST7735(5, 18, 19);  // pantalla SPI

// variable para LoRa
String nodoID = "NODO3_LORA";  // id único del nodo LoRa
float temp = 0.0, hum = 0.0;  // variables para temperatura y humedad
int nivelAgua = 0;  // nivel de agua del depósito

// función para medir nivel de agua con ultrasónico
int medirNivelAgua() {
  long duracion;
  digitalWrite(pinUltrasonicoTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pinUltrasonicoTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinUltrasonicoTrigger, LOW);

  duracion = pulseIn(pinUltrasonicoEcho, HIGH);
  int distancia = duracion * 0.034 / 2;

  return distancia;  // retorna distancia (nivel de agua)
}

// configuración inicial
void setup() {
  Serial.begin(115200);  // iniciar comunicación serie para debug
  
  // inicializar LoRa
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(915E6)) {  // frecuencia 915 MHz
    Serial.println("Falló la inicialización de LoRa");  // si LoRa falla
    while (1);
  }
  
  Wire.begin();  // iniciar I2C para el sensor AHT10
  aht.begin();  // iniciar AHT10
  
  // inicializar pantalla
  tft.initR(INITR_144GREENTAB);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextWrap(true);
  tft.setTextSize(1);
  tft.println("Nodo 3 LoRa");

  // pines de sensores
  pinMode(pinHumResistivo, INPUT);
  pinMode(pinHumCapacitivo, INPUT);
  pinMode(pinLdr, INPUT);
  pinMode(pinUltrasonicoTrigger, OUTPUT);
  pinMode(pinUltrasonicoEcho, INPUT);
}

// loop principal
void loop() {
  // leer temperatura y humedad con AHT10
  sensors_event_t tempEvent, humEvent;
  aht.getEvent(&humEvent, &tempEvent);
  temp = tempEvent.temperature;  // temperatura
  hum = humEvent.relative_humidity;  // humedad
  
  // leer humedad de suelo
  int humedadSueloResistivo = analogRead(pinHumResistivo);  // sensor resistivo
  int humedadSueloCapacitivo = analogRead(pinHumCapacitivo);  // sensor capacitivo
  
  // leer luz ambiental
  int luz = analogRead(pinLdr);  // sensor de luz
  
  // medir nivel de agua
  nivelAgua = medirNivelAgua();

  // mostrar datos en pantalla
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.printf("Temp: %.1fC\nHum: %.1f%%\nLuz: %d\nHum Suelo (Resistivo): %d\nHum Suelo (Capacitivo): %d\nNivel Agua: %d\n", temp, hum, luz, humedadSueloResistivo, humedadSueloCapacitivo, nivelAgua);
  
  // generar mensaje para enviar por LoRa
  String mensaje = nodoID + ";Temp:" + String(temp) + ";Hum:" + String(hum) + ";Luz:" + String(luz) + ";HumRes:" + String(humedadSueloResistivo) + ";HumCap:" + String(humedadSueloCapacitivo) + ";NivelAgua:" + String(nivelAgua);
  
  // enviar mensaje por LoRa
  LoRa.beginPacket();
  LoRa.print(mensaje);
  LoRa.endPacket();
  
  // esperar 5 segundos antes de la siguiente medición
  delay(5000);
}
