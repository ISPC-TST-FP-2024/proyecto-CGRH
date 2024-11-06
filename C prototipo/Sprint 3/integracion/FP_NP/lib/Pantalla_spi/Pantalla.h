#ifndef PANTALLA_H
#define PANTALLA_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

class Pantalla {
  private:
    Adafruit_ST7735 tft;

  public:
    Pantalla(uint8_t cs, uint8_t dc, uint8_t rst);
    void inicializar();
    void mostrarMensaje(const String& mensaje);
};

#endif
