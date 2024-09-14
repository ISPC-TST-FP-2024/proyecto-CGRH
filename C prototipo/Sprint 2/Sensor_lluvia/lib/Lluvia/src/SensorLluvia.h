#ifndef SENSOR_LLUVIA_H
#define SENSOR_LLUVIA_H

class SensorLluvia {
public:
    SensorLluvia(int pin);
    void begin();
    bool isRaining();

private:
    int _pin;
};

#endif
