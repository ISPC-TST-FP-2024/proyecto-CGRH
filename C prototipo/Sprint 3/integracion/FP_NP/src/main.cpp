#include <Arduino.h>
#include "Pantalla.h"
#include "Comunicacion.h"
#include "Sensor_nivel.h"
#include "Actuadores.h"

// Configuración WiFi y servidor
const char* SSID = "TuSSID";
const char* PASSWORD = "TuPassword";
const String URL_SERVIDOR = "http://tu-servidor.com/api/datos";

// Pines y configuración de LoRa
const int LORA_CS = 18;
const int LORA_RST = 14;
const int LORA_IRQ = 26;

// UUIDs BLE
const String SERVICE_UUID = "12345678-1234-1234-1234-1234567890ab";
const String CHARACTERISTIC_UUID = "87654321-4321-4321-4321-0987654321ab";

// Pines para sensores y actuadores
#define TRIGGER_PIN 4
#define ECHO_PIN 2
#define RELE_BOMBA 26
#define RELE_LUZ 25

// Instancias de clases
Pantalla pantalla(5, 17, 16);
Comunicacion comunicacion;
Sensor_nivel reserva_agua;
Actuadores actuadores;

void enviarDatos(const String& datos) {
    if (comunicacion.enviarDatosHTTP(URL_SERVIDOR, datos)) {
        Serial.println("Datos enviados con éxito.");
    } else {
        Serial.println("Error al enviar datos.");
    }
}

void setup() {
    Serial.begin(115200);
    pantalla.inicializar();
    pantalla.mostrarMensaje("Iniciando...");

    comunicacion.iniciarBLE("Nodo Central", SERVICE_UUID, CHARACTERISTIC_UUID);
    comunicacion.iniciarLoRa(915E6, LORA_CS, LORA_RST, LORA_IRQ);
    comunicacion.conectarWiFi(SSID, PASSWORD);

    actuadores.configurarPin(RELE_BOMBA);
    actuadores.configurarPin(RELE_LUZ);
}

void loop() {
    // Adquirir datos del sensor de nivel de agua
    int nivelAgua = reserva_agua.medirNivelAgua(TRIGGER_PIN, ECHO_PIN);
    Serial.print("Nivel de agua: ");
    Serial.println(nivelAgua);

    // Encender o apagar la bomba según el nivel
    if (nivelAgua > 10) {
        actuadores.encender(RELE_BOMBA);
    } else {
        actuadores.apagar(RELE_BOMBA);
    }

    // Verificar si hay datos de BLE o LoRa
    String datosBLE = comunicacion.hayDatosBLE() ? comunicacion.obtenerDatosBLE() : "";
    String datosLoRa = comunicacion.hayDatosLoRa() ? comunicacion.obtenerDatosLoRa() : "";

    // Crear payload JSON con todos los datos
    String payload = "{";
    payload += "\"nivelAgua\":" + String(nivelAgua) + ",";
    payload += "\"datosBLE\":\"" + datosBLE + "\",";
    payload += "\"datosLoRa\":\"" + datosLoRa + "\"";
    payload += "}";

    // Enviar los datos al servidor
    enviarDatos(payload);

    // Actualizar la pantalla con el nivel de agua
    pantalla.mostrarMensaje("Nivel: " + String(nivelAgua));

    delay(5000);  // Esperar 5 segundos antes de la siguiente lectura
}
