/*
 *
 * DAVIDE CARITÀ - PROGETTO IOT
 *        Smart Greenhouse
 * 
 */

#include <Arduino.h>

#include "config.h"
#include "UserInput.h"

#include "kernel/Scheduler.h"
#include "kernel/Logger.h"
#include "kernel/MsgService.h"
#include "kernel/BTHandler.h"

#include "model/Greenhouse.h"

#include "tasks/BlinkTask.h"
#include "tasks/CoolingControlTask.h"
#include "tasks/ModeManagerTask.h"
#include "tasks/WaterControlTask.h"

Scheduler sched;

Greenhouse* pGreenhouse;
UserInput* pUserInput;
BTHandler* pBtHandler;

void setup() {
  MsgService.init();
  sched.init(100);

  Logger.log("Smart Greenhouse");
  
  pGreenhouse = new Greenhouse();
  pGreenhouse->init();

  pUserInput = new UserInput();
  pUserInput->init();

  pBtHandler = new BTHandler(BT_RX_PIN, BT_TX_PIN);
  pBtHandler->init();

  Task* pWateringBlinkTask = new BlinkTask(LED_WATER_PIN);
  pWateringBlinkTask->init(100);
  pWateringBlinkTask->setActive(false);

  Task* pCoolingBlinkTask = new BlinkTask(LED_FAN_PIN);
  pCoolingBlinkTask->init(100);
  pCoolingBlinkTask->setActive(false);

  Task* pModeManagerTask = new ModeManagerTask(pGreenhouse, pUserInput, pBtHandler);
  pModeManagerTask->init(100);

  Task* pWaterControlTask = new WaterControlTask(pGreenhouse, pWateringBlinkTask);
  pWaterControlTask->init(200);

  Task* pCoolingControlTask = new CoolingControlTask(pGreenhouse, pCoolingBlinkTask);
  pCoolingControlTask->init(200);

  sched.addTask(pModeManagerTask);
  sched.addTask(pWaterControlTask);
  sched.addTask(pWateringBlinkTask);
  sched.addTask(pCoolingControlTask);
  sched.addTask(pCoolingBlinkTask);
}

void loop() {
    sched.schedule();
}