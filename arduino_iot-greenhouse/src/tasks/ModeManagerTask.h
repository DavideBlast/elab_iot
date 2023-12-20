#ifndef __MODE_SWITCH_TASK__
#define __MODE_SWITCH_TASK__

#include "kernel/Task.h"
#include "kernel/BTHandler.h"
#include "model/Greenhouse.h"
#include "UserInput.h"
#include "tasks/BlinkTask.h"

#include "devices/Button.h"
#include "devices/Led.h"

class ModeManagerTask: public Task {

public:
  ModeManagerTask(Greenhouse* pGreenhouse, UserInput* pUserInput, BTHandler* pBTHandler); 
  void tick();

private:  
  //String currentState;

  void setState(int state);
  long elapsedTimeInState();
  void notifyModeChange();

  enum { IDLE, CHECK, WATERING, COOLING} state;
  long stateTimestamp;
  int count = 0;

  Greenhouse* pGreenhouse;
  UserInput* pUserInput;
  BTHandler* pBTHandler;
};

#endif