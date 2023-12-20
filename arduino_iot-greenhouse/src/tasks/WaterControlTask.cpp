#include "tasks/WaterControlTask.h"
#include "Arduino.h"
#include "config.h"
#include "kernel/Logger.h"

WaterControlTask::WaterControlTask(Greenhouse* pGreenhouse, BlinkTask* pBlinkTask){
    this->pGreenhouse = pGreenhouse;
    this->pBlinkTask = pBlinkTask;
    setState(OFF);
}

void WaterControlTask::tick(){
    switch (state){
    case ON: {
        pBlinkTask->setActive(true);
        pGreenhouse->turnWaterPumpOn();
        if (!pGreenhouse->isWatering()) {
            Logger.log("WaterControlTask: Turning water pump off");
            setState(OFF);
        }
        break;
    }
    case OFF: {
        pBlinkTask->setActive(false);
        pGreenhouse->turnWaterPumpOff();
        if (pGreenhouse->isWatering()) {
            Logger.log("WaterControlTask: Turning water pump on");
            setState(ON);
        }
        break;       
    }
    }
}

void WaterControlTask::setState(int s){
    state = s;
    stateTimestamp = millis();
}

long WaterControlTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}

  