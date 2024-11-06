#include "Pantalla.h"

Pantalla::Pantalla(uint8_t cs, uint8_t dc, uint8_t rst) : tft(cs, dc, rst) {}

void Pantalla::inicializar() {
    tft.initR(INITR_BLACKTAB);
    tft.setRotation(2);
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(1);
}

void Pantalla::mostrarMensaje(const String& mensaje) {
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(0, 0);
    tft.println(mensaje);
}
