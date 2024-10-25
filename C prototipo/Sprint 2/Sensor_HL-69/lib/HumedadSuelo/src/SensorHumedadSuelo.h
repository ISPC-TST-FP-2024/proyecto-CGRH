#ifndef SENSOR_HUMEDAD_SUELO_H
#define SENSOR_HUMEDAD_SUELO_H

class SensorHumedadSuelo {
public:
    SensorHumedadSuelo(int pin);
    void begin();
    int readHumedad();

private:
    int _pin;
};

#endif
