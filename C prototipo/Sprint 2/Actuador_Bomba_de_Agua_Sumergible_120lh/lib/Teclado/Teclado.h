#ifndef TECLADO_H
#define TECLADO_H

#include <Arduino.h>

// Clase para manejar un teclado matricial
class Teclado {
public:
    // Constructor
    Teclado(int fila1, int fila2, int fila3, int fila4, int col1, int col2, int col3);

    void iniciar();         // Inicializa el teclado
    char leerTecla();      // Lee la tecla presionada

private:
    // Pines de filas y columnas
    int _fila1, _fila2, _fila3, _fila4;
    int _col1, _col2, _col3;

    // Método para verificar si una tecla está presionada
    bool esTeclaPresionada(int fila, int col);
};

#endif
