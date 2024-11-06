#include "Comunicacion.h"

Comunicacion::Comunicacion() : datosBLERecibidos(false), datosLoRaRecibidos(false) {}

void Comunicacion::iniciarBLE(const String& nombreNodo, const String& serviceUUID, const String& characteristicUUID) {
    BLEDevice::init(nombreNodo.c_str());
    BLEServer *servidor = BLEDevice::createServer();
    BLEService *servicio = servidor->createService(serviceUUID.c_str());

    caracteristica = servicio->createCharacteristic(
        characteristicUUID.c_str(),
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
    );

    caracteristica->setValue("Esperando datos...");
    servicio->start();
}

void Comunicacion::iniciarLoRa(long frecuencia, int cs, int rst, int irq) {
    LoRa.setPins(cs, rst, irq);
    if (!LoRa.begin(frecuencia)) {
        Serial.println("Error al iniciar LoRa.");
        while (true);
    }
    Serial.println("LoRa iniciado correctamente.");
}

void Comunicacion::conectarWiFi(const char* ssid, const char* password) {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi conectado.");
}

bool Comunicacion::enviarDatosHTTP(const String& url, const String& payload) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(url);
        http.addHeader("Content-Type", "application/json");

        int httpResponseCode = http.POST(payload);
        http.end();

        return httpResponseCode > 0 && httpResponseCode < 400;
    } else {
        Serial.println("No hay conexión WiFi.");
        return false;
    }
}

bool Comunicacion::hayDatosBLE() {
    return datosBLERecibidos;
}

bool Comunicacion::hayDatosLoRa() {
    return datosLoRaRecibidos;
}

String Comunicacion::obtenerDatosBLE() {
    datosBLERecibidos = false;
    return datosBLE;
}

String Comunicacion::obtenerDatosLoRa() {
    datosLoRaRecibidos = false;
    return datosLoRa;
}
