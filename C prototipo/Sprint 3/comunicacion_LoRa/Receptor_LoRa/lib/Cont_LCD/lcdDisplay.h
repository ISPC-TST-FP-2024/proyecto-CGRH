#ifndef LCDDISPLAY_H
#define LCDDISPLAY_H

//#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class lcdDisplay {
private:
    LiquidCrystal_I2C lcd;
public:
    lcdDisplay();
    void init();
    void showMessage(String msg);
};

#endif
