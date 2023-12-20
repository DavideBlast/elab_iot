#include "tasks/CoolingControlTask.h"
#include "Arduino.h"
#include "config.h"
#include "kernel/Logger.h"

CoolingControlTask::CoolingControlTask(Greenhouse* pGreenhouse, BlinkTask* pBlinkTask){
    this->pGreenhouse = pGreenhouse;
    this->pBlinkTask = pBlinkTask;
    setState(OFF);
}
  
void CoolingControlTask::tick(){
    switch (state){
    case ON: {
        pBlinkTask->setActive(true);
        pGreenhouse->turnCoolingFanOn();
        if (!pGreenhouse->isCooling()) {
            Logger.log("CoolingControlTask: Turning cooling fan off");
            setState(OFF);
        }
        break;
    }
    case OFF: {
        pBlinkTask->setActive(false);
        pGreenhouse->turnCoolingFanOff();
        if (pGreenhouse->isCooling()) {
            Logger.log("CoolingControlTask: Turning cooling fan on");
            setState(ON);
        }
        break;       
    }
    }
}


void CoolingControlTask::setState(int s){
    state = s;
    stateTimestamp = millis();
}

long CoolingControlTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}
