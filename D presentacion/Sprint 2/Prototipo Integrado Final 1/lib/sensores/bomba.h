#ifndef BOMBA_H
#define BOMBA_H

// Definir el pin de control del relé de la bomba de agua
#define PIN_RELE_BOMBA  25  // Cambiar al pin que estés utilizando para controlar el relé

// Funciones para activar y desactivar la bomba
void inicializarBomba();   // Inicializar el pin de control de la bomba
void activarBomba();       // Activar la bomba
void desactivarBomba();    // Desactivar la bomba

#endif
