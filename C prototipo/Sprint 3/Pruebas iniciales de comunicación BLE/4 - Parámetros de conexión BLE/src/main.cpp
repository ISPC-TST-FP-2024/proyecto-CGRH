#include <Arduino.h>
#include "ble_ajuste_parametros.h"

BLE_AjusteParametros moduloBLE;

void setup() {
    Serial.begin(115200);

    // Inicializar BLE
    moduloBLE.iniciarBLE();

    // Ajustar el intervalo de publicidad a 500 ms (valor por defecto: 1000 ms)
    moduloBLE.ajustarParametrosPublicidad(500);  // Intervalo en milisegundos
}

void loop() {
    // Verificar el estado de la conexión
    moduloBLE.verificarConexion();

    // Ejemplo de notificación periódica
    if (moduloBLE.isDispositivoConectado()) {
        moduloBLE.notificarClientes("Mensaje BLE desde ESP32");
    }

    delay(1000); // Esperar 1 segundo entre notificaciones
}
