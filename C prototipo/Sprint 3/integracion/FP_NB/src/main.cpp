#include <Arduino.h>
#include <Wire.h>
#include <AHT10.h>  // nueva librería para el sensor AHT10
#include <BluetoothSerial.h>  // librería para Bluetooth
#include <esp_system.h>  // para generar el id único
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>


// Configuración de pines
#define TFT_CS    5
#define TFT_RST   16
#define TFT_DC    17
#define RELE_LED 25
#define RELE_BOMBA 26
#define TRIGGER 4
#define ECHO 2
#define DISTANCIA_MINIMA_AGUA 10
#define LDR 8
#define HumSueloRES 10
#define HumSueloCAP 11
BluetoothSerial SerialBT;

// Identificadores de nodos
String nodoID = "Nodo_2";

// Variables de sensores
float temperatura, humedad, luzAmbiente;
int nivelAgua, humedadSueloCap, humedadSueloRes;

// Pantalla y sensores
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
AHT10 aht;



// Función para inicializar pantalla y sensores
void setupDisplay() {
    Wire.begin();
    aht.begin();
    tft.initR(INITR_BLACKTAB);
    tft.setRotation(1);
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(0, 0);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextWrap(true);
    tft.setTextSize(1);
    tft.println("Nodo_1");
}
// Función para medir nivel de agua
int medirNivelAgua() {
    digitalWrite(TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER, LOW);
    long duracion = pulseIn(ECHO, HIGH);
    return duracion * 0.034 / 2;
}
float leerLuzAmbiente() {
    int lecturaLDR = analogRead(LDR);  // Leer el pin analógico
    float luzAmbiente = (lecturaLDR / 4095.0) * 100.0;  // Convertir a porcentaje
    Serial.print("Luz Ambiente: ");
    Serial.println( luzAmbiente);
    return  luzAmbiente;
}
void controlIluminacion() {
    luzAmbiente = leerLuzAmbiente();
    if (luzAmbiente < 20.0) {  // Si la luz ambiente es baja (menos de 20%)
        digitalWrite(RELE_LED, HIGH);  // Encender luz
        Serial.println("Iluminación activada.");
    } else {
        digitalWrite(RELE_LED, LOW);  // Apagar luz
        Serial.println("Iluminación desactivada.");
    }
}
void controlBomba() {
    nivelAgua = medirNivelAgua();
    if (nivelAgua < DISTANCIA_MINIMA_AGUA) {
        digitalWrite(RELE_BOMBA, HIGH);  // Activar la bomba si el nivel de agua es bajo
        Serial.println("Bomba activada.");
    } else {
        digitalWrite(RELE_BOMBA, LOW);  // Apagar la bomba
        Serial.println("Bomba desactivada.");
    }
}
void leerHumedadSuelo() {
    humedadSueloCap = analogRead(HumSueloCAP);
    humedadSueloRes = analogRead(HumSueloRES);
    Serial.print("Humedad Suelo Capacitivo: ");
    Serial.println(humedadSueloCap);
    Serial.print("Humedad Suelo Resistivo: ");
    Serial.println(humedadSueloRes);
}
void enviarMensajePorBle(int luz, int humedadSueloResistivo, int humedadSueloCapacitivo, int nivelAgua) {
  String mensaje = nodoID + ";Temp:" + String(temperatura) + ";Hum:" + String(humedad) + ";Luz:" + String(luzAmbiente) + ";HumRes:" + String(humedadSueloRes) + ";HumCap:" + String(humedadSueloCap) + ";NivelAgua:" + String(nivelAgua);
  SerialBT.println(mensaje);
}
// Función principal de setup
void setup() {
    Serial.begin(9600);
    pinMode(RELE_LED, OUTPUT);
    pinMode(RELE_BOMBA, OUTPUT);
    pinMode(TRIGGER, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(LDR,INPUT);
    digitalWrite(RELE_LED, LOW);
    digitalWrite(RELE_BOMBA, LOW);
  }

  // Función principal de loop
void loop() {

        nivelAgua = medirNivelAgua();
    if (nivelAgua < DISTANCIA_MINIMA_AGUA) {
        digitalWrite(RELE_BOMBA, HIGH);
    } else {
        digitalWrite(RELE_BOMBA, LOW);
    }
}


