#ifndef TIRA_LED_H
#define TIRA_LED_H

#include <Adafruit_NeoPixel.h>

class TiraLED {
public:
    TiraLED(uint8_t pin, uint16_t numLeds);
    void begin();
    void encender(uint32_t color);
    void apagar();
    void recorrer(uint32_t color, uint16_t delayTime);

private:
    Adafruit_NeoPixel strip;
};

#endif
