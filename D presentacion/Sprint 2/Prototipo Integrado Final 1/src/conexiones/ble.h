#ifndef BLUETOOTH_H
#define BLUETOOTH_H

// Función para inicializar el módulo Bluetooth
// Opción para especificar un nombre de dispositivo Bluetooth
void iniciarBle(const char* nombreDispositivo = "ESP32");

// Función para manejar las comunicaciones Bluetooth
// Escucha y responde a comandos recibidos
void manejarBle();

// Función para mostrar el estado del Bluetooth (conectado/desconectado)
void estadoBLE();

#endif
