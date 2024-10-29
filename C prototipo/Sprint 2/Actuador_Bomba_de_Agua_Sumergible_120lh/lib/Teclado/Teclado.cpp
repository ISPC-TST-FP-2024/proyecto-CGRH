#include "Teclado.h"

// Constructor
Teclado::Teclado(int fila1, int fila2, int fila3, int fila4, int col1, int col2, int col3) 
    : _fila1(fila1), _fila2(fila2), _fila3(fila3), _fila4(fila4), _col1(col1), _col2(col2), _col3(col3) {
}

// Inicializa el teclado
void Teclado::iniciar() {
    pinMode(_fila1, OUTPUT);
    pinMode(_fila2, OUTPUT);
    pinMode(_fila3, OUTPUT);
    pinMode(_fila4, OUTPUT);
    pinMode(_col1, INPUT_PULLUP);
    pinMode(_col2, INPUT_PULLUP);
    pinMode(_col3, INPUT_PULLUP);
}

// Lee la tecla presionada
char Teclado::leerTecla() {
    for (int i = 0; i < 4; i++) {
        digitalWrite(_fila1 + i, LOW); // Activa la fila correspondiente

        for (int j = 0; j < 3; j++) {
            if (digitalRead(_col1 + j) == LOW) {
                delay(50); // Debounce
                if (digitalRead(_col1 + j) == LOW) {
                    digitalWrite(_fila1 + i, HIGH); // Desactiva la fila
                    return '1' + (i * 3 + j); // Devuelve un caracter según la tecla
                }
            }
        }

        digitalWrite(_fila1 + i, HIGH); // Desactiva la fila
    }
    return '\0'; // Devuelve un carácter nulo si no se presiona ninguna tecla
}
