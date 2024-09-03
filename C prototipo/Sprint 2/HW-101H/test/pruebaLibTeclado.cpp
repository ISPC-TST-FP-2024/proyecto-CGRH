/*Ejemplo 1*/

#include <Arduino.h>
#include <Wire.h>
#include "teclado.h"

Teclado teclado(32, 33, 25, 26, 27, 14, 12); // Instanciar el objeto Teclado con los pines asignados

void setup()
{
    Serial.begin(115200);
    teclado.iniciar(); // Inicializar el teclado
}

void loop()
{
    char tecla = teclado.leerTecla(); // Leer la tecla presionada
    if (tecla)
    { // Si se presionó una tecla
        Serial.print("Tecla presionada: ");
        Serial.println(tecla);
    }
}