#ifndef SENSOR_LDR_H
#define SENSOR_LDR_H

class SensorLDR {
public:
    SensorLDR(int pin);
    void begin();
    int readLightLevel();

private:
    int _pin;
};

#endif
