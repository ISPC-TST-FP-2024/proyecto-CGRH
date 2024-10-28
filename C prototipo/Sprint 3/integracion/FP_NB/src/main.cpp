#include <Arduino.h>
#include <AHT10.h>  // Nueva librería para el sensor AHT10
#include <BluetoothSerial.h>  // Librería para Bluetooth
#include <esp_system.h>  // Para generar el id único
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <BLEDevice.h>
#include <BLEClient.h>
#include <BLEUtils.h>
#include <BLE2902.h>
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

// variables de sensores
float temperatura, humedad, luzAmbiente;
int nivelAgua, humedadSueloCap, humedadSueloRes,distancia,Reintentos = 1;
bool Iluminacion,Bomba,bleConectado;
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
AHT10 aht10;  

///////////////////////////////////////////////////////////////////////////////
//////                    Funciones de Manejo de BLE               ///////////
/////////////////////////////////////////////////////////////////////////////

// Definición de los UUIDs para el servicio y la característica
BLEUUID serviceUUID("12345678-1234-1234-1234-1234567890ab"); // UUID del servicio
BLEUUID characteristicUUID("87654321-4321-4321-4321-abcdefabcdef"); // UUID de la característica
BLERemoteCharacteristic* NodoCliente; // Puntero a la característica remota
BLEClient* cliente; // Puntero al cliente BLE

// Variables de datos
String nodoID = "Nodo_2";

// Función para conectar al servidor BLE
bool conectaralServer(BLEAddress serverAddress) {
  cliente = BLEDevice::createClient(); // Crear un cliente BLE
  Serial.print("Intentando conectar a: ");
  Serial.println(serverAddress.toString().c_str()); // la dirección a la que intenta conectar

  // Intentar conectar al servidor BLE
  if (cliente->connect(serverAddress)) {
    Serial.println("Conectado al servidor BLE");
  } else {
    Serial.println("No se pudo conectar al servidor BLE");
    return false; // Fallo en la conexión
  }
  
  // Obtener el servicio del servidor
  BLERemoteService* service = cliente->getService(serviceUUID);
  if (service == nullptr) {
    Serial.println("Servicio no encontrado.");
    cliente->disconnect(); 
    return false; // No se encontró el servicio
  }
  
  // Obtener la característica del servicio
   NodoCliente = service->getCharacteristic(characteristicUUID);
  if ( NodoCliente == nullptr) {
    Serial.println("Característica no encontrada.");
    cliente->disconnect(); 
    return false; // No se encontró la característica
  }

  Serial.println("Nodo servidor encontrado y conectado correctamente.");
  return true; // Conexión exitosa
}
bool initializeBLE() {
    // Inicializar el dispositivo BLE
    BLEDevice::init("");

    // Obtener el escáner BLE y configurarlo
    BLEScan* scan = BLEDevice::getScan(); 
    scan->setActiveScan(true); // Habilitar escaneo activo
    Serial.println("Escaneando por dispositivos BLE...");
    scan->start(5); // Escanear durante 5 segundos

    // Dirección MAC del servidor BLE (ajusta a la dirección de tu servidor)
    BLEAddress serverAddress("08:d1:f9:a4:f4:ea"); // Reemplazado con la dirección MAC correcta

    // Intentar conectar al servidor
    return conectaralServer(serverAddress); // Devuelve true si se conecta, false si no
}

// Función para enviar datos por BLE
void enviarDatosPorBLE() {
    if (cliente != nullptr && cliente->isConnected()) { // Verifica si hay conexión
        String mensaje = nodoID + ";Temp:" + String(temperatura) + 
                         ";Hum:" + String(humedad) + 
                         ";Luz:" + String(luzAmbiente) + 
                         ";NivelAgua:" + String(nivelAgua) + 
                         ";HumCap:" + String(humedadSueloCap) + 
                         ";HumRes:" + String(humedadSueloRes) + 
                         ";Distancia:" + String(distancia) + 
                         ";Reintentos:" + String(Reintentos) + 
                         ";Iluminacion:" + String(Iluminacion) + 
                         ";Bomba:" + String(Bomba) + 
                         ";BLEConectado:" + String(bleConectado);

        NodoCliente->writeValue(mensaje.c_str(), mensaje.length()); // Enviar el mensaje por BLE
        Serial.println("Datos enviados: " + mensaje); // Confirmación en el monitor serie
    } else {
        Serial.println("Error: Dispositivo receptor no conectado.");
    }
}

void enviarDatos() {
    if (cliente != nullptr && cliente->isConnected()) { // Verifica si el cliente está conectado
        // Crear un string JSON con los datos a enviar
        String data = "{";
        data += "\"temperatura\":" + String(temperatura) + ",";
        data += "\"humedad\":" + String(humedad) + ",";
        data += "\"luzAmbiente\":" + String(luzAmbiente) + ",";
        data += "\"nivelAgua\":" + String(nivelAgua) + ",";
        data += "\"humedadSueloCap\":" + String(humedadSueloCap) + ",";
        data += "\"humedadSueloRes\":" + String(humedadSueloRes) + ",";
        data += "\"distancia\":" + String(distancia) + ",";
        data += "\"Iluminacion\":" + String(Iluminacion) + ",";
        data += "\"Bomba\":" + String(Bomba) + ",";
        data += "\"bleConectado\":" + String(bleConectado) + "}";

        // Enviar datos a la característica del servidor
        NodoCliente->writeValue(data.c_str(), data.length());
        Serial.println("Datos enviados: " + data); // Imprime los datos enviados
    } else {
        Serial.println("Error: Dispositivo receptor no conectado.");
    }
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
   
   
    // Mostrar estado de los actuadores
    tft.print("Iluminacion: ");
    tft.println(Iluminacion ? "Activada" : "Desactivada");
    tft.print("Bomba: ");
    tft.println(Bomba ? "Activada" : "Desactivada");
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

///////////////////////////////////////////////////////////////////////////////
//////                          SetUp                            ///////////
/////////////////////////////////////////////////////////////////////////////

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
    tft.println("Iniciando Nodo 2...");
if (initializeBLE()) {
        Serial.println("Conectado al servidor.");
    } else {
        Serial.println("No se pudo conectar al servidor.");
    }

 
  if (!SD.begin()) {
        Serial.println("Error al montar la tarjeta SD. Continuando ejecución...");
    } else {
        Serial.println("Tarjeta SD montada correctamente.");
    }

}

///////////////////////////////////////////////////////////////////////////////
//////                          Loop                               ///////////
/////////////////////////////////////////////////////////////////////////////

void loop() {
 setupDisplay();
    // Si no está conectado, intenta escanear nuevamente
    if (!cliente) {
        initializeBLE(); // Inicializa la conexión BLE si no está conectado
    }
     else {
          enviarDatosPorBLE(); // Envía los datos por BLE
        }
    

    // Imprimir el estado de la conexión
    if (cliente) {
        Serial.println("Nodo conectado a un dispositivo");
    } else {
        Serial.println("Nodo no conectado a ningún dispositivo");
    }
     mostrarDatosPantalla();
     mostrarDatosSensoresYActuadores();

    delay(1000); // Pausa de 1 segundo entre cada iteración del loop
}
