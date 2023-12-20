#ifndef __GREENHOUSE__
#define __GREENHOUSE__

#include <Arduino.h>
#include "devices/Led.h"
#include "devices/WaterPump.h"
#include "devices/Fan.h"

class Greenhouse {
    
public: 
    Greenhouse();
    
    void init();
    
    double getCurrentTemperature();
    double getCurrentSoilMoisture();

    bool isWaterPumpOn();
    void turnWaterPumpOn();
    void turnWaterPumpOff();

    bool isCoolingFanOn();
    void turnCoolingFanOn();
    void turnCoolingFanOff();

    bool isIdle();
    bool isCheck();
    bool isWatering();
    bool isCooling();
    
    void setIdleState();
    void setCheckState();
    void setWateringState();
    void setCoolingState();

    float sampleSoilMoistureLevel();
    float sampleTemperatureLevel();

private:

    float currentSoilMoisture;
    float currentTemperature;
    
    enum {IDLE, CHECK, WATERING, COOLING} state;

    WaterPump* pWaterPump;
    Fan* pCoolingFan;
};


#endif