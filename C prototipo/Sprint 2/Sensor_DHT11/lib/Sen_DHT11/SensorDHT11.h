#ifndef SENSOR_DHT11_H
#define SENSOR_DHT11_H

#include <DHT.h>

class SensorDHT11 {
public:
    SensorDHT11(int pin);
    void begin();
    float readTemperature();
    float readHumidity();

private:
    DHT dht;
};

#endif
