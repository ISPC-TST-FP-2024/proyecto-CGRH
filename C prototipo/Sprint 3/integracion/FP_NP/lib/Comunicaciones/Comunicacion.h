#ifndef COMUNICACION_H
#define COMUNICACION_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <LoRa.h>
#include <BLEDevice.h>

class Comunicacion {
public:
    Comunicacion();
    void iniciarBLE(const String& nombreNodo, const String& serviceUUID, const String& characteristicUUID);
    void iniciarLoRa(long frecuencia, int cs, int rst, int irq);
    void conectarWiFi(const char* ssid, const char* password);
    bool enviarDatosHTTP(const String& url, const String& payload);
    bool hayDatosBLE();
    bool hayDatosLoRa();
    String obtenerDatosBLE();
    String obtenerDatosLoRa();

private:
    BLECharacteristic *caracteristica;
    bool datosBLERecibidos;
    bool datosLoRaRecibidos;
    String datosBLE;
    String datosLoRa;
};

#endif
