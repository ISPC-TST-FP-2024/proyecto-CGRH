#ifndef SENSOR_ULTRASONICO_H
#define SENSOR_ULTRASONICO_H

class SensorUltrasonico {
public:
    SensorUltrasonico(int triggerPin, int echoPin);
    void begin();
    long readDistance();

private:
    int _triggerPin;
    int _echoPin;
};

#endif
