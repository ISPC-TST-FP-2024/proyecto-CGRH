#ifndef TECLADO_H
#define TECLADO_H

#include <Arduino.h>

class Teclado {
public:
    Teclado(int fila1, int fila2, int fila3, int fila4, int col1, int col2, int col3, int col4);
    void iniciar();
    char leerTecla();

private:
    int filas[4];
    int columnas[4];
    char teclado[4][4]; // Matriz de teclas
};

#endif // TECLADO_H
