#ifndef __BTHANDLER__
#define __BTHANDLER__

#include "config.h"
#include "devices/Button.h"
#include <Wire.h>
#include "SoftwareSerial.h"
#include "model/Greenhouse.h"
#include "Arduino.h"

class BTHandler {
    
public:

    BTHandler(int rxPin, int txPin);

    void init();
    void sync();
    
    String readMsg();

private:
    SoftwareSerial channel;
    String msg;
};

#endif