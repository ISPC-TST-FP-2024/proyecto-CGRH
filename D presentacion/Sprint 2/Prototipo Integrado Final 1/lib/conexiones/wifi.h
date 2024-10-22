#ifndef WIFI_H
#define WIFI_H

#include <WiFi.h>

// Declaración de funciones para la gestión de WiFi
void iniciarWiFi();                          // Función para iniciar WiFi con credenciales guardadas
void manejarWiFi();                          // Función para manejar la conexión WiFi
void verEstadoWiFi();                        // Función para mostrar el estado actual de la conexión WiFi
void conectarWiFiManual(const char* ssid, const char* password);  // Función para conectar a WiFi de manera manual
void desconectarWiFi();                      // Función para desconectar del WiFi

#endif
