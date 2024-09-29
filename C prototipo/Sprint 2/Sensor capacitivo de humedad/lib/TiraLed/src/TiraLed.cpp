#include "TiraLED.h"

TiraLED::TiraLED(uint8_t pin, uint16_t numLeds) : strip(numLeds, pin, NEO_GRB + NEO_KHZ800) {}

void TiraLED::begin() {
    strip.begin();
    strip.show();  // Inicializa apagada
}

void TiraLED::encender(uint32_t color) {
    for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, color);
    }
    strip.show();
}

void TiraLED::apagar() {
    strip.clear();
    strip.show();
}

void TiraLED::recorrer(uint32_t color, uint16_t delayTime) {
    for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, color);
        strip.show();
        delay(delayTime);
    }
}
