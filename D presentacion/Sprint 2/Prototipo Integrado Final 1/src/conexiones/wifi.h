#ifndef WIFI_H
#define WIFI_H

// Inicializar conexión WiFi, con opción de pasar SSID y contraseña manualmente
void iniciarWiFi(const char* ssid = nullptr, const char* password = nullptr);

// Manejar la conexión WiFi y enviar datos
void manejarWiFi();

// Mostrar el estado actual de la conexión WiFi (IP, velocidad, RSSI, etc.)
void estadoWiFi();

// Iniciar modo Access Point
void iniciarAP();

#endif
