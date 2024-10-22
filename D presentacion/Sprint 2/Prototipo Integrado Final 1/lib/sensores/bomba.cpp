#include <Arduino.h>
#include "bomba.h"

// Inicializar el pin del relé de la bomba de agua
void inicializarBomba() {
    pinMode(PIN_RELE_BOMBA, OUTPUT);  // Configurar el pin como salida
    desactivarBomba();                // Asegurarse de que la bomba esté desactivada al inicio
}

// Activar la bomba (enciende el relé)
void activarBomba() {
    digitalWrite(PIN_RELE_BOMBA, LOW);  // La mayoría de los relés se activan con una señal LOW
    Serial.println("Bomba activada");
}

// Desactivar la bomba (apaga el relé)
void desactivarBomba() {
    digitalWrite(PIN_RELE_BOMBA, HIGH);  // La mayoría de los relés se desactivan con una señal HIGH
    Serial.println("Bomba desactivada");
}
