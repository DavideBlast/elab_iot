#ifndef FAN_H
#define FAN_H

#include "Arduino.h"

class Fan {
  public:
    Fan(int pin, int dir1, int dir2);
    void turnOn();
    void turnOff();
    bool isFanOn();
    
  private:
    int pin;
    int dir1;
    int dir2;
    bool isOn;
};

#endif
