#ifndef ACTUADORES_H
#define ACTUADORES_H

class Actuadores {
  public:
    void configurarPin(int pin);
    void encender(int pin);
    void apagar(int pin);
};

#endif
