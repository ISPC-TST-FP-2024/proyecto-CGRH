#ifndef MODULO_RELE_H
#define MODULO_RELE_H

class ModuloRele {
public:
    ModuloRele(int pin);
    void begin();
    void encender();
    void apagar();

private:
    int _pin;
};

#endif
