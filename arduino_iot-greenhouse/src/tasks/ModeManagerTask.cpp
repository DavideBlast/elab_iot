#include "ModeManagerTask.h"
#include "UserInput.h"
#include "Arduino.h"
#include "devices/Button.h"
#include "devices/Led.h"
#include "config.h"
#include "kernel/Logger.h"
#include "kernel/MsgService.h"

//#define IDLE_TIME 10800000 // 10.800.000 ms = 3 ore
//#define WATERING_TIME 10000 // 10.000 ms = 10 secondi
//#define COOLING_TIME 600000 // 600.000 ms = 10 minuti

#define IDLE_TIME 10000
#define WATERING_TIME 5000
#define COOLING_TIME 5000

#define HUMIDITY_THRESHOLD -150 //TO-DO: STABILIRE GIUSTO THRESHOLD
#define TEMPERATURE_THRESHOLD 25 //TO-DO: STABILIRE GIUSTO THRESHOLD

ModeManagerTask::ModeManagerTask(Greenhouse* pGreenhouse, UserInput* pUserInput, BTHandler* pBTHandler){
    this->pGreenhouse = pGreenhouse;
    this->pUserInput = pUserInput;
    this->pBTHandler = pBTHandler;
    setState(IDLE);
    notifyModeChange();
}

void ModeManagerTask::tick(){
    switch (state){    
    case IDLE: {
        pUserInput->sync();
        if (this->elapsedTimeInState() > IDLE_TIME){
            pGreenhouse->setCheckState();
            setState(CHECK);
            notifyModeChange();
        } else if (pUserInput->isPumpButtonPressed()){
            pGreenhouse->setWateringState();
            setState(WATERING);
            notifyModeChange();
        } else if (pUserInput->isFanButtonPressed()){
            pGreenhouse->setCoolingState();
            setState(COOLING);
            notifyModeChange();
        } else {
            String msg = pBTHandler->readMsg();
            if (msg == "won"){
                pGreenhouse->setWateringState();
                setState(WATERING);
                notifyModeChange();
            } else if (msg == "fon"){
                pGreenhouse->setCoolingState();
                setState(COOLING);
                notifyModeChange();
            }
        }
        break;
    }
    case CHECK: {
        if (pGreenhouse->sampleSoilMoistureLevel() < HUMIDITY_THRESHOLD){
            pGreenhouse->setWateringState();
            setState(WATERING);
            notifyModeChange();    
            break;
        } else if (pGreenhouse->sampleTemperatureLevel() > TEMPERATURE_THRESHOLD){
            pGreenhouse->setCoolingState();
            setState(COOLING);
            notifyModeChange();
            break;
        }
        pGreenhouse->setIdleState();
        setState(IDLE);
        notifyModeChange();
        break;
    }
    case WATERING: {
        pUserInput->sync();
        if (this->elapsedTimeInState() > WATERING_TIME){
            pGreenhouse->setCheckState();
            setState(CHECK);
            notifyModeChange();
            break;
        } else if (pUserInput->isPumpButtonPressed()){
            pGreenhouse->setIdleState();
            setState(IDLE);
            notifyModeChange();
            break;
        } else if (pBTHandler->readMsg() == "woff"){
            pGreenhouse->setIdleState();
            setState(IDLE);
            notifyModeChange();
            break;
        }
        break;
    }
    case COOLING: {
        pUserInput->sync();
        if (this->elapsedTimeInState() > COOLING_TIME){
            pGreenhouse->setCheckState();
            setState(CHECK);
            notifyModeChange();
            break;
        } else if (pUserInput->isFanButtonPressed()){
            pGreenhouse->setIdleState();
            setState(IDLE);
            notifyModeChange();
            break;
        } else if (pBTHandler->readMsg() == "foff"){
            pGreenhouse->setIdleState();
            setState(IDLE);
            notifyModeChange();
            break;
        }
        break;
    }
    }
}

void ModeManagerTask::setState(int s){
    state = s;
    stateTimestamp = millis();
}

long ModeManagerTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}

void ModeManagerTask::notifyModeChange(){
    String currentState = "";
    switch (state){
    case IDLE:
        currentState = "id";
        break;
    case CHECK:
        currentState = "ch";
        break;
    case WATERING:
        currentState = "wa";
        break;
    case COOLING:
        currentState = "co";
        break;
    }
    MsgService.sendMsg("gr:" + currentState);
}