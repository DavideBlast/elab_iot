#ifndef WATER_PUMP_H
#define WATER_PUMP_H

#include "Arduino.h"

class WaterPump {
public:
    WaterPump(int relayPin);
    void turnOn();
    void turnOff();
    bool isPumpOn();

private:
    int relayPin;
    bool isOn;
};

#endif
