#ifndef MYLORACLASS_H
#define MYLORACLASS_H

#include "Vextpin.h" 
#include "global.h"

class MyLoRaClass {
public:
    MyLoRaClass();  // Constructor
    void displayJoining(); // Mantener el nombre original
    void displayJoined();  // Mantener el nombre original
    void displaySending(); // Mantener el nombre original
    void displayAck();     // Mantener el nombre original
};

#endif // MYLORACLASS_H
