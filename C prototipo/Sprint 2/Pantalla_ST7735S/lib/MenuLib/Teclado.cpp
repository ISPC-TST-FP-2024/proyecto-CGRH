#include "Teclado.h"

Teclado::Teclado(int fila1, int fila2, int fila3, int fila4, int col1, int col2, int col3, int col4) {
    filas[0] = fila1;
    filas[1] = fila2;
    filas[2] = fila3;
    filas[3] = fila4;
    
    columnas[0] = col1;
    columnas[1] = col2;
    columnas[2] = col3;
    columnas[3] = col4;

    // Definir el mapeo de teclas
    teclado[0][0] = '1'; teclado[0][1] = '2'; teclado[0][2] = '3'; teclado[0][3] = 'A';
    teclado[1][0] = '4'; teclado[1][1] = '5'; teclado[1][2] = '6'; teclado[1][3] = 'B';
    teclado[2][0] = '7'; teclado[2][1] = '8'; teclado[2][2] = '9'; teclado[2][3] = 'C';
    teclado[3][0] = '*'; teclado[3][1] = '0'; teclado[3][2] = '#'; teclado[3][3] = 'D';
}

void Teclado::iniciar() {
    for (int i = 0; i < 4; i++) {
        pinMode(filas[i], OUTPUT);
        digitalWrite(filas[i], HIGH);
        pinMode(columnas[i], INPUT_PULLUP);
    }
}

char Teclado::leerTecla() {
    for (int i = 0; i < 4; i++) {
        digitalWrite(filas[i], LOW); // Activar fila
        for (int j = 0; j < 4; j++) {
            if (digitalRead(columnas[j]) == LOW) {
                delay(50); // debounce
                while (digitalRead(columnas[j]) == LOW); // Esperar a que se suelte
                digitalWrite(filas[i], HIGH); // Desactivar fila
                return teclado[i][j]; // Devolver la tecla
            }
        }
        digitalWrite(filas[i], HIGH); // Desactivar fila
    }
    return '\0'; // Sin tecla presionada
}
