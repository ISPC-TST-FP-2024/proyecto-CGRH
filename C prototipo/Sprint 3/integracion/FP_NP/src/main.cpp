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
#include <SD.h>

// Configuración de pines
#define TFT_CS    15
#define TFT_RST   4
#define TFT_DC    2
#define LORA_SCK  18
#define LORA_MISO 19
#define LORA_MOSI 23
#define LORA_CS   5
#define LORA_RST  14
#define LORA_IRQ  27
#define RELE_LED 17
#define RELE_BOMBA 26
#define TRIGGER 13
#define ECHO 12
#define DISTANCIA_MINIMA_AGUA 10
#define LDR 34
#define HumSueloRES 35
#define HumSueloCAP 36
#define SD_CS 7
///////////////////////////////////////////////////////////////////////////////
//////                        varibles                              //////////
/////////////////////////////////////////////////////////////////////////////
// variables de sensores
float temperatura, humedad, luzAmbiente;
int nivelAgua, humedadSueloCap, humedadSueloRes,distancia,Reintentos = 1;
bool Iluminacion,Bomba,loRaConectado,bleConectado;
// pantalla y sensores

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
AHT10 aht10;   
String loraData = "";
bool loraDataReceived = false;
// wi-fi
const char* ssid = "Vitto";
const char* password = "vittorio10";
const char* serverName = "http://192.168.100.18:5001/api";  // url del servidor para enviar los datos


///////////////////////////////////////////////////////////////////////////////
////// Inicialización de BLE y configuración del nombre del servidor//////////
/////////////////////////////////////////////////////////////////////////////
String nodoID_BLE = "Nodo1";  // id del nodo ble, modificamos para que sea nodo 1

BLEServer* server;
BLECharacteristic* characteristic;

// Clase para manejar eventos de conexión y desconexión
#define SERVICE_UUID        "12345678-1234-1234-1234-1234567890ab"
#define CHARACTERISTIC_UUID "87654321-4321-4321-4321-abcdefabcdef"


// Variable para verificar el estado de conexión del dispositivo
bool deviceConnected = false;

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* server) {
    deviceConnected = true;  // Cambia el estado cuando el cliente se conecta
    Serial.println("Cliente conectado.");
  }

  void onDisconnect(BLEServer* server) {
    deviceConnected = false;  // Cambia el estado cuando el cliente se desconecta
    Serial.println("Cliente desconectado.");
    BLEDevice::startAdvertising();  // Reinicia la publicidad para permitir nuevas conexiones
  }
};
void inicializarServidorBLE() {

  BLEDevice::init("ESP32 Servidor Central");

  // Obtiene y muestra la dirección BLE del servidor en el monitor serial
  BLEAddress serverAddress = BLEDevice::getAddress();
  Serial.print("Dirección del Servidor BLE: ");
  Serial.println(serverAddress.toString().c_str());

  // Crea el servidor y configura los callbacks para manejar conexiones y desconexiones
  server = BLEDevice::createServer();
  server->setCallbacks(new MyServerCallbacks());

  // Creación del servicio BLE usando el UUID definido
  BLEService *service = server->createService(SERVICE_UUID);

  // Creación de la característica del servicio con permiso de escritura
  characteristic = service->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_WRITE
                    );

  // Añade un descriptor a la característica para habilitar notificaciones si es necesario
  characteristic->addDescriptor(new BLE2902());

  // Inicia el servicio BLE
  service->start();

  // Configuración de la publicidad del servicio BLE
  BLEAdvertising *advertising = BLEDevice::getAdvertising();
  advertising->addServiceUUID(SERVICE_UUID);
  advertising->setScanResponse(true);
  BLEDevice::startAdvertising();

  Serial.println("Servidor BLE listo y anunciando...");
}


///////////////////////////////////////////////////////////////////////////////
//////    Inicialización de WiFi y configuración del nombre de WiFi///////////
/////////////////////////////////////////////////////////////////////////////

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
void reconectarWiFi() {
  for (int intentos = 0; intentos < Reintentos; intentos++) {
    WiFi.disconnect();  // Desconecta cualquier intento previo
    WiFi.begin(ssid, password);  // Inicia la conexión
    Serial.print("Intentando reconectar a WiFi...");

    for (int i = 0; i < 5; i++) {  // puntos
      delay(1000);
      Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\nConectado a WiFi nuevamente.");
      return;  // Sale de la función si se conecta
    }
  }

  Serial.println("\nNo se pudo reconectar a WiFi tras varios intentos.");
}

///////////////////////////////////////////////////////////////////////////////
//////   Inicialización de LoRa y configuración del nombre de Lora ///////////
/////////////////////////////////////////////////////////////////////////////

String nodoID_LoRa = "Nodo1";  // id del nodo lora
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

///////////////////////////////////////////////////////////////////////////////
//////          Funciones de Manejo de Datos de Conexión           ///////////
/////////////////////////////////////////////////////////////////////////////

void guardarDatosEnSD(String data) {
    File file = SD.open("/datos.csv", FILE_APPEND);
    if (file) {
        file.println(data);
        file.close();
        Serial.println("Datos guardados en SD.");
    } else {
        Serial.println("Error al guardar los datos en SD.");
    }
}

// enviar datos al servidor
void enviarDatosServidor(String nodoID, float temp, float hum, int nivelAgua, float luz, int humSueloCap, int humSueloRes, int distancia, bool iluminacion, bool bomba) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(serverName);

        String postData = "id=" + nodoID +
                         "&temp=" + String(temp) +
                         "&hum=" + String(hum) +
                          "&luz=" + String(luz) + 
                          "&hum_cap=" + String(humSueloCap) +
                          "&hum_res=" + String(humSueloRes) + 
                          "&nivel_agua=" + String(nivelAgua) +
                          "&distancia=" + String(distancia) + 
                          "&iluminacion=" + (iluminacion ? "1" : "0") +
                          "&bomba=" + (bomba ? "1" : "0");

        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        int httpResponseCode = http.POST(postData);
        if (httpResponseCode > 0) {
            Serial.println("Datos enviados al servidor");
        } else {
            Serial.println("Error enviando los datos: " + String(httpResponseCode));
            guardarDatosEnSD(postData);  // Guardar en SD si falla el envío
        }
        http.end();
    } else {
         String postData = "data";
        guardarDatosEnSD(postData);  // Guardar en SD si no hay conexión WiFi
    }
}

// Manejo de errores BLE
void handleBLEError(esp_err_t error) {
    switch (error) {
        case ESP_ERR_NO_MEM:
            Serial.println("Error: No hay suficiente memoria para la conexión.");
            break;
        case ESP_ERR_INVALID_STATE:
            Serial.println("Error: El servidor BLE está en un estado incorrecto.");
            break;
        case ESP_ERR_TIMEOUT:
            Serial.println("Error: Tiempo de conexión agotado.");
            break;
        default:
            Serial.printf("Error desconocido: 0x%x\n", error);
            break;
    }
}


// procesar datos recibidos por ble
void procesarDatosBLE(String receivedData) {
    // Verificamos que los datos vienen con el formato correcto:
    // "NODO_ID;temp:xx;hum:xx;luz:xx;humcap:xx;humres:xx;nivelagua:xx;distancia:xx;ilum:xx;bomba:xx"
    
    String idNodo = receivedData.substring(0, receivedData.indexOf(";"));
    receivedData = receivedData.substring(receivedData.indexOf(";") + 1);  // quitar el id

    temperatura = receivedData.substring(receivedData.indexOf("temp:") + 5, receivedData.indexOf(";hum:")).toFloat();
    humedad = receivedData.substring(receivedData.indexOf("hum:") + 4, receivedData.indexOf(";luz:")).toFloat();
    luzAmbiente = receivedData.substring(receivedData.indexOf("luz:") + 4, receivedData.indexOf(";humcap:")).toFloat();
    humedadSueloCap = receivedData.substring(receivedData.indexOf("humcap:") + 7, receivedData.indexOf(";humres:")).toInt();
    humedadSueloRes = receivedData.substring(receivedData.indexOf("humres:") + 7, receivedData.indexOf(";nivelagua:")).toInt();
    nivelAgua = receivedData.substring(receivedData.indexOf("nivelagua:") + 10, receivedData.indexOf(";distancia:")).toInt();
    distancia = receivedData.substring(receivedData.indexOf("distancia:") + 10, receivedData.indexOf(";ilum:")).toInt();
    Iluminacion = receivedData.substring(receivedData.indexOf("ilum:") + 5, receivedData.indexOf(";bomba:")) == "1";
    Bomba = receivedData.substring(receivedData.indexOf("bomba:") + 6) == "1"; // Suponiendo que el valor sea "1" o "0"

    Serial.println("Datos BLE recibidos del nodo: " + idNodo);

    // Enviar los datos al servidor
    enviarDatosServidor(idNodo, temperatura, humedad, nivelAgua, luzAmbiente, humedadSueloCap, humedadSueloRes, distancia, Iluminacion, Bomba);
}

void enviarConfirmacion(String idNodo) {
    String mensaje = "Datos recibidos correctamente del nodo: " + idNodo;
    // Aquí envías el mensaje a través de BLE
    characteristic->setValue(mensaje.c_str()); // Asigna el mensaje a la característica
    characteristic->notify(); // Envía notificación al emisor
    Serial.println("Confirmación enviada al nodo: " + idNodo);
}
// procesar datos recibidos por lora
void procesarDatosLoRa() {
    // Asegurarse de que los datos vienen con el mismo formato que BLE
    String idNodo = loraData.substring(0, loraData.indexOf(";"));
    loraData = loraData.substring(loraData.indexOf(";") + 1);  // quitar el id

    temperatura = loraData.substring(loraData.indexOf("temp:") + 5, loraData.indexOf(";hum:")).toFloat();
    humedad = loraData.substring(loraData.indexOf("hum:") + 4, loraData.indexOf(";luz:")).toFloat();
    luzAmbiente = loraData.substring(loraData.indexOf("luz:") + 4, loraData.indexOf(";humcap:")).toFloat();
    humedadSueloCap = loraData.substring(loraData.indexOf("humcap:") + 7, loraData.indexOf(";humres:")).toInt();
    humedadSueloRes = loraData.substring(loraData.indexOf("humres:") + 7, loraData.indexOf(";nivelagua:")).toInt();
    nivelAgua = loraData.substring(loraData.indexOf("nivelagua:") + 10, loraData.indexOf(";distancia:")).toInt();
    distancia = loraData.substring(loraData.indexOf("distancia:") + 10, loraData.indexOf(";ilum:")).toInt();
    Iluminacion = loraData.substring(loraData.indexOf("ilum:") + 5, loraData.indexOf(";bomba:")) == "1";
    Bomba = loraData.substring(loraData.indexOf("bomba:") + 6) == "1"; // Suponiendo que el valor sea "1" o "0"
  
    Serial.println("Datos LoRa recibidos del nodo: " + idNodo);

    // Enviar los datos al servidor
    enviarDatosServidor(idNodo, temperatura, humedad, nivelAgua, luzAmbiente, HumSueloCAP, HumSueloRES, distancia, Iluminacion, Bomba);
}


//Reenviar datos desde la SD
void reenviarDatosDesdeSD() {
    if (WiFi.status() == WL_CONNECTED) {
        File file = SD.open("/datos.csv");
        if (file) {
            while (file.available()) {
                String data = file.readStringUntil('\n');
                HTTPClient http;
                http.begin(serverName);
                http.addHeader("Content-Type", "application/x-www-form-urlencoded");
                int httpResponseCode = http.POST(data);
                if (httpResponseCode > 0) {
                    Serial.println("Datos reenviados: " + data);
                }
                http.end();
            }
            file.close();
            SD.remove("/datos.csv");  // Eliminar archivo después de enviar
        }
    }
}
///////////////////////////////////////////////////////////////////////////////
//////          Funciones de Manejo de Datos de Conexión           ///////////
/////////////////////////////////////////////////////////////////////////////




// Función para medir nivel de agua
int medirNivelAgua() {
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

    // Comprobar si el sensor capacitivo está fallando
    if (humedadSueloCap == 0 || humedadSueloCap == 1023) {  // Valores fuera de rango
        Serial.println("¡Alarma! El sensor de humedad del suelo capacitivo está fallando.");
      
    }

    // Comprobar si el sensor resistivo está fallando
    if (humedadSueloRes == 0 || humedadSueloRes == 1023) {  // Valores fuera de rango
        Serial.println("¡Alarma! El sensor de humedad del suelo resistivo está fallando.");
        
    }
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
// IMPLEMENTAR CAMBIO DE PANTALLA POR QUE NO ENTRA TODOS LOS DATOS 
void mostrarDatosPantalla() {
    tft.fillScreen(ST77XX_BLACK); // Limpiar la pantalla con el color negro
    tft.setCursor(0, 0);          // Establecer el cursor en la posición inicial
    tft.setTextColor(ST77XX_WHITE);// Establecer el color del texto a blanco
    tft.setTextWrap(true);        // Habilitar el ajuste de texto
    tft.setTextSize(1);           // Establecer el tamaño del texto

      tft.print("Temperatura: ");
    tft.println(temperatura);
    tft.print("Humedad: ");
    tft.println(humedad);
    tft.print("Luz Ambiente: ");
    tft.println(luzAmbiente);
    tft.print("Nivel de Agua: ");
    tft.println(nivelAgua);
    tft.print("Humedad Suelo (Capacitivo): ");
    tft.println(humedadSueloCap);
    tft.print("Humedad Suelo (Resistivo): ");
    tft.println(humedadSueloRes);
        
    tft.print("Dispositivos conectados: ");
    tft.print("Wi-Fi: ");
    if (WiFi.status() == WL_CONNECTED) {
        tft.println("Conectado");
    } else {
        tft.println("No conectado");
    }

    // Mostrar estado de BLE
    tft.print("BLE: ");
    if (deviceConnected) {
        tft.println("Nodo conectado");
    } else {
        tft.println("No conectado");
    }

    // Mostrar estado de LoRa
    tft.print("LoRa: ");
    if (loraDataReceived) {
        tft.println("Datos recibidos");
    } else {
        tft.println("Esperando datos");
    }

    // Mostrar estado de los actuadores
       tft.print("Iluminacion: ");
    tft.println(Iluminacion ? "Activada" : "Desactivada");
    tft.print("Bomba: ");
    tft.println(Bomba ? "Activada" : "Desactivada");
    }
void mostrarDatosSensoresYActuadores() {
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
}

float leerLuzAmbiente() {
    int lecturaLDR = analogRead(LDR);  // Leer el pin analógico
    float luzAmbiente = (lecturaLDR / 4095.0) * 100.0;  // Convertir a porcentaje
    Serial.print("Luz Ambiente: ");
    Serial.println( luzAmbiente);
    return  luzAmbiente;
}

void controlIluminacion() {
    int maxReintentos = 3;  // Máximo de reintentos antes de disparar la alarma

    luzAmbiente = leerLuzAmbiente();
    
    if (luzAmbiente < 20.0) {  // Si la luz ambiente es baja (menos de 20%)
        digitalWrite(RELE_LED, HIGH);  // Encender luz
        Iluminacion = true;  // Actualizar el estado de la iluminación
        Serial.println("Iluminación activada.");
        Reintentos = 0;  // Reiniciar contador de reintentos porque la luz se activó correctamente
    } else {
        digitalWrite(RELE_LED, LOW);   // Apagar luz
        Iluminacion = false;  // Actualizar el estado de la iluminación
        Serial.println("Iluminación desactivada.");
        Reintentos = 0;  // Reiniciar contador porque la luz se apagó correctamente
    }

    // Comprobar si no se puede activar la iluminación
    if (Iluminacion == false && luzAmbiente < 20.0) {
        Reintentos++;
        if (Reintentos >= maxReintentos) {
            Serial.println("¡Alarma! No se puede activar la iluminación después de varios intentos.");
            // podemos  enviar una notificación
        }
    }
}

void setup() {
  Serial.begin(9600);
    pinMode(TFT_CS, OUTPUT);
    pinMode(TFT_RST, OUTPUT);
    pinMode(TFT_DC, OUTPUT);
    pinMode(LORA_SCK, OUTPUT);
    pinMode(LORA_MISO, INPUT);
    pinMode(LORA_MOSI, OUTPUT);
    pinMode(LORA_CS, OUTPUT);
    pinMode(LORA_RST, OUTPUT);
    pinMode(LORA_IRQ, INPUT);
    pinMode(RELE_LED, OUTPUT);
    pinMode(RELE_BOMBA, OUTPUT);
    pinMode(TRIGGER, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(DISTANCIA_MINIMA_AGUA, INPUT);
    pinMode(LDR, INPUT);
    pinMode(HumSueloRES, INPUT);
    pinMode(HumSueloCAP, INPUT);
    Wire.begin(21, 22);
  setupDisplay();

  tft.println("Iniciando Nodo 1...");
Serial.begin(9600);
 // configurar wi-fi
  setupWiFi();
   delay(200);
  // configurar LoRa
  iniciarLoRa();
   delay(200);
  // Inicialización de la comunicación serial
  
  if (!SD.begin()) {
        Serial.println("Error al montar la tarjeta SD. Continuando ejecución...");
    } else {
        Serial.println("Tarjeta SD montada correctamente.");
    }
     delay(200);

  inicializarServidorBLE();
   delay(200);
}


void loop() {
    if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Conexión WiFi perdida, intentando reconectar...");
    reconectarWiFi();  // Llamo a la funcion para intentar reconectar
  }


  // verificar si llegaron datos por lora
  if (loraDataReceived) {
    procesarDatosLoRa();
    loraDataReceived = false;
  }
  
  // Verificación de la conexión del cliente para recibir datos
  if (deviceConnected) {
    // Obtiene y muestra los datos recibidos, si están disponibles
    String receivedData = characteristic->getValue().c_str();
    if (receivedData.length() > 0) {
      procesarDatosBLE(receivedData);
      Serial.println("Datos recibidos: " + receivedData);
      characteristic->setValue("");  // Limpia el valor después de procesar los datos
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
 if (receivedData) {
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

    if (WiFi.status() == WL_CONNECTED) {
        reenviarDatosDesdeSD();  // Reenviar datos almacenados
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
}
