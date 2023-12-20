#include "model/Greenhouse.h"
#include "config.h"
#include "devices/WaterPump.h"
#include "devices/Fan.h"
#include "kernel/MsgService.h"
#include "SoftwareSerial.h"
#include <Wire.h>

Greenhouse::Greenhouse(){
}

void Greenhouse::init(){
    pWaterPump = new WaterPump(PUMP_PIN);
    pCoolingFan = new Fan(FAN_ENABLE_PIN, FAN_DIR_A_PIN, FAN_DIR_B_PIN);

    MsgService.init();

    state = IDLE;
}

double Greenhouse::getCurrentTemperature(){
    return currentTemperature;
}

double Greenhouse::getCurrentSoilMoisture(){
    return currentSoilMoisture;
}

/* WATER PUMP*/

bool Greenhouse::isWaterPumpOn(){
   return pWaterPump->isPumpOn();
}

void Greenhouse::turnWaterPumpOn(){
    pWaterPump->turnOn();
}

void Greenhouse::turnWaterPumpOff(){
    pWaterPump->turnOff();
}

/* COOLING FAN */

bool Greenhouse::isCoolingFanOn(){
    return pCoolingFan->isFanOn();
}

void Greenhouse::turnCoolingFanOn(){
    pCoolingFan->turnOn();
}

void Greenhouse::turnCoolingFanOff(){
    pCoolingFan->turnOff();
}

/* STATES */

bool Greenhouse::isIdle(){
    return state == IDLE;
}

bool Greenhouse::isCheck(){
    return state == CHECK;
}

bool Greenhouse::isWatering(){
    return state == WATERING;
}

bool Greenhouse::isCooling(){
    return state == COOLING;
}

void Greenhouse::setIdleState(){
    state = IDLE;
}

void Greenhouse::setCheckState(){
    state = CHECK;
}

void Greenhouse::setWateringState(){
    state = WATERING;
}

void Greenhouse::setCoolingState(){
    state = COOLING;
}

/* SAMPLE */

float Greenhouse::sampleSoilMoistureLevel(){
    float soilMoisture = 4; //Se inferiore di -150, va in watering
    return soilMoisture;
}


float Greenhouse::sampleTemperatureLevel(){
    float temperature = 23; //Se maggiore di 25, va in cooling
    return temperature;
}

/*

float Greenhouse::sampleTemperatureLevel(){
    if (MsgService.isMsgAvailable()) {
        Msg* msg = MsgService.receiveMsg();
        String msgContent = msg->getContent();

        int commaIndex = msgContent.indexOf(',');
        String soilMoistureString = msgContent.substring(0, commaIndex);

        currentSoilMoisture = atof(soilMoistureString.c_str());
    }

    return currentSoilMoisture;
}

float Greenhouse::sampleTemperatureLevel(){
    if (MsgService.isMsgAvailable()) {
        Msg* msg = MsgService.receiveMsg();
        String msgContent = msg->getContent();

        int commaIndex = msgContent.indexOf(',');
        String temperatureString = msgContent.substring(commaIndex + 1);

        currentTemperature = atof(temperatureString.c_str());
    }
    
    return currentTemperature;
}

*/