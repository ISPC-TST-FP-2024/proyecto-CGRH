#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <AHT10.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <LoRa.h>
#include <HTTPClient.h>

// Configuración de pines
#define TFT_CS    5
#define TFT_RST   16
#define TFT_DC    17
#define LORA_SCK  18
#define LORA_MISO 19
#define LORA_MOSI 23
#define LORA_CS   5
#define LORA_RST  14
#define LORA_IRQ  26
#define RELE_LED 25
#define RELE_BOMBA 26
#define TRIGGER 4
#define ECHO 2
#define DISTANCIA_MINIMA_AGUA 10
#define LDR 8
#define HumSueloRES 10
#define HumSueloCAP 11

// wi-fi
const char* ssid = "DZS_5380";
const char* password = "dzsi123456789";
const char* serverName = "http://192.168.55.104/api";  // url del servidor para enviar los datos

// identificadores de los nodos
String nodoID_BLE = "nodo1";  // id del nodo ble, modificamos para que sea nodo 1
String nodoID_LoRa = "nodo1";  // id del nodo lora

// configuracion ble
#define SERVICE_UUID        "6e400001-b5a3-f393-e0a9-e50e24dcca9e"
#define CHARACTERISTIC_UUID "6e400003-b5a3-f393-e0a9-e50e24dcca9e"
BLECharacteristic *pCharacteristic;
bool dataReceived = false;
String bleData = "";

// configuracion lora
String loraData = "";
bool loraDataReceived = false;

// variables de sensores
float temperatura, humedad, luzAmbiente;
int nivelAgua, humedadSueloCap, humedadSueloRes,distancia,Reintentos = 5;
bool Iluminacion,Bomba,loRaConectado;
// pantalla y sensores
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
AHT10 aht10;

// funcion para inicializar wi-fi
void setupWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("conectando a wifi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println(" conectado a wifi.");
}

// enviar datos al servidor
void enviarDatosServidor(String nodoID, float temp, float hum, int nivelAgua, float luz, int humSueloCap, int humSueloRes) {
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);

    String postData = "id=" + nodoID + "&temp=" + String(temp) + "&hum=" + String(hum) +
                      "&luz=" + String(luz) + "&hum_cap=" + String(humSueloCap) +
                      "&hum_res=" + String(humSueloRes) + "&nivel_agua=" + String(nivelAgua);

    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int httpResponseCode = http.POST(postData);
    if (httpResponseCode > 0) {
      Serial.println("datos enviados al servidor");
    } else {
      Serial.println("error enviando los datos: " + String(httpResponseCode));
    }
    http.end();
  } else {
    Serial.println("no conectado a wifi.");
  }
}

// funcion para medir nivel de agua con hc-sr04
int medirNivelAgua() {
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);

  // calcular el tiempo del pulso de echo
  long duracion = pulseIn(ECHO, HIGH);

  // calcular distancia en cm
  int distancia = duracion * 0.034 / 2;
  return distancia;
}

// procesar datos recibidos por ble
void procesarDatosBLE() {
  // aca verifcamos que  los datos vienen con el formato:
  // "NODO_ID;temp:xx;hum:xx;luz:xx;humcap:xx;humres:xx;nivelagua:xx"
  String idNodo = bleData.substring(0, bleData.indexOf(";"));
  bleData = bleData.substring(bleData.indexOf(";") + 1);  // quitar el id
  temperatura = bleData.substring(bleData.indexOf("temp:") + 5, bleData.indexOf(";hum:")).toFloat();
  humedad = bleData.substring(bleData.indexOf("hum:") + 4, bleData.indexOf(";luz:")).toFloat();
  luzAmbiente = bleData.substring(bleData.indexOf("luz:") + 4, bleData.indexOf(";humcap:")).toFloat();
  humedadSueloCap = bleData.substring(bleData.indexOf("humcap:") + 7, bleData.indexOf(";humres:")).toInt();
  humedadSueloRes = bleData.substring(bleData.indexOf("humres:") + 7, bleData.indexOf(";nivelagua:")).toInt();
  nivelAgua = bleData.substring(bleData.indexOf("nivelagua:") + 10).toInt();

  Serial.println("datos ble recibidos del nodo: " + idNodo);

  // enviar los datos al servidor
  enviarDatosServidor(idNodo, temperatura, humedad, nivelAgua, luzAmbiente, humedadSueloCap, humedadSueloRes);
}
void enviarConfirmacion(String idNodo) {
    String mensaje = "Datos recibidos correctamente del nodo: " + idNodo;
    
    // Aquí envías el mensaje a través de BLE
    // Suponiendo que tienes un objeto BLE llamado 'ble'
   // ble.write(mensaje.c_str(), mensaje.length()); // Cambia 'ble' por tu objeto BLE si tiene otro nombre
   // Serial.println("Confirmación enviada al nodo: " + idNodo);
}
// procesar datos recibidos por lora
void procesarDatosLoRa() {
  // aca verificamos que los datos vienen con el mismo formato que ble
  String idNodo = loraData.substring(0, loraData.indexOf(";"));
  loraData = loraData.substring(loraData.indexOf(";") + 1);  // quitar el id
  temperatura = loraData.substring(loraData.indexOf("temp:") + 5, loraData.indexOf(";hum:")).toFloat();
  humedad = loraData.substring(loraData.indexOf("hum:") + 4, loraData.indexOf(";luz:")).toFloat();
  luzAmbiente = loraData.substring(loraData.indexOf("luz:") + 4, loraData.indexOf(";humcap:")).toFloat();
  humedadSueloCap = loraData.substring(loraData.indexOf("humcap:") + 7, loraData.indexOf(";humres:")).toInt();
  humedadSueloRes = loraData.substring(loraData.indexOf("humres:") + 7, loraData.indexOf(";nivelagua:")).toInt();
  nivelAgua = loraData.substring(loraData.indexOf("nivelagua:") + 10).toInt();

  
  
  Serial.println("datos lora recibidos del nodo: " + idNodo);

  // enviar los datos al servidor
  enviarDatosServidor(idNodo, temperatura, humedad, nivelAgua, luzAmbiente, humedadSueloCap, humedadSueloRes);
}
void controlBomba() {
    nivelAgua = medirNivelAgua();
    if (nivelAgua < DISTANCIA_MINIMA_AGUA) {
        digitalWrite(RELE_BOMBA, HIGH);  // Activar la bomba si el nivel de agua es bajo
        Bomba = true;               // Actualizar el estado de la bomba
        Serial.println("Bomba activada.");
    } else {
        digitalWrite(RELE_BOMBA, LOW);   // Apagar la bomba
        Bomba = false;              // Actualizar el estado de la bomba
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
void setupDisplay() {
    Wire.begin();
    aht10.begin();
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
int MedirNivelAgua() {
    digitalWrite(TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER, LOW);
    long duracion = pulseIn(ECHO, HIGH);
    return duracion * 0.034 / 2;
       if (duracion <= 0) {
        Serial.println("Error: No se recibió respuesta del sensor.");
        return -1;  // si hay  error en la medicion
    } else if (distancia < 0 || distancia > 400) { // Ajusta los valores según tu sensor
        Serial.println("Error: Lectura fuera de rango.");
        return -1;  // si hay  error en la medicion
    } else {
        Serial.print("Distancia medida: ");
        Serial.print(distancia);
        Serial.println(" cm");
        return distancia;  // nos debuelve la distancia medida
    }
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
        Iluminacion = true;       // Actualizar el estado de la iluminación
        Serial.println("Iluminación activada.");
    } else {
        digitalWrite(RELE_LED, LOW);   // Apagar luz
        Iluminacion = false;      // Actualizar el estado de la iluminación
        Serial.println("Iluminación desactivada.");
    }
}
// Función para iniciar LoRa
bool iniciarLoRa() {
    LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);

    // Intentar iniciar LoRa
    for (int i = 0; i < Reintentos; i++) {
        if (LoRa.begin(915E6)) { //no se que esto 
            Serial.println("Sistema LoRa listo.");
            loRaConectado = true;  // Conexión exitosa
            return true;           // Conexión exitosa
        } else {
            Serial.println("Fallo al iniciar LoRa. Intentando de nuevo...");
            delay(1000); // Esperamos un segundo antes de intentar nuevamente
        }
    }
    
    Serial.println("No se pudo iniciar LoRa después de varios intentos. Continuando sin LoRa...");
    loRaConectado = false; // Conexión fallida
    return false;          // Conexión fallida
}

// Función para verificar la conexión LoRa
void verificarConexionLoRa() {
    if (!loRaConectado) {
        Serial.println("Verificando conexión LoRa...");
        if (iniciarLoRa()) {
            Serial.println("LoRa reconectado.");
        }
    }
}
// callback ble para recibir datos
class MyCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    bleData = pCharacteristic->getValue().c_str();
    if (bleData.length() > 0) {
      dataReceived = true;
    }
  }
};


void setup() {
  Serial.begin(9600);

  // iniciar pantalla
  tft.initR(INITR_BLACKTAB);  
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(0, 0);
  tft.println("iniciando...");


  // configurar wi-fi
  setupWiFi();
  // configurar LoRa
  iniciarLoRa();
  // configurar ble
  BLEDevice::init("nodo central cultivo");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
  pCharacteristic->setCallbacks(new MyCallbacks());
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->start();


}

void loop() {
 

  // verificar si llegaron datos por ble
  if (dataReceived) {
    procesarDatosBLE();
    dataReceived = false;
  }

  // verificar si llegaron datos por lora
  if (loraDataReceived) {
    procesarDatosLoRa();
    loraDataReceived = false;
  }
   
  Serial.println("=========== ESTADO DE CONEXIONES ===========");
    
  // Mostrar estado de Wi-Fi
  Serial.print("Wi-Fi: ");
  if (WiFi.status() == WL_CONNECTED) {
  Serial.println("Conectado");
  } else {
  Serial.println("No conectado");
    }

    // Mostrar estado de BLE
 Serial.print("BLE: ");
 if (dataReceived) {
 Serial.println("Nodo conectado");
 } else {
  Serial.println("No conectado");
 }

    // Mostrar estado de LoRa
 Serial.print("LoRa: ");
    if (loraDataReceived) {
        Serial.println("Datos recibidos");
    } else {
        Serial.println("Esperando datos");
    }
// Llama a la función para verificar la conexión LoRa
verificarConexionLoRa();
    // Mostrar los datos de los sensores
Serial.println("=========== DATOS DE LOS SENSORES ===========");
Serial.print("Temperatura: ");
Serial.println(temperatura);
Serial.print("Humedad: ");
Serial.println(humedad);
Serial.print("Luz Ambiente: ");
Serial.println(luzAmbiente);
Serial.print("Nivel de Agua: ");
Serial.println(nivelAgua);
Serial.print("Humedad Suelo (Capacitivo): ");
Serial.println(humedadSueloCap);
Serial.print("Humedad Suelo (Resistivo): ");
Serial.println(humedadSueloRes);

    // Mostrar los datos de los actuadores
Serial.println("=========== ESTADO DE ACTUADORES ===========");
   
Serial.print("Iluminacion: ");
Serial.println(Iluminacion);
Serial.print("Bomba: ");
Serial.println(Bomba);

Serial.println("=============================================");

  delay(5000);  // esperar 5 segundos antes de medir otra vez
}
