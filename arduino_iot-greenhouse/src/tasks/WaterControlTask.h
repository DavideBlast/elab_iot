#ifndef __WATER_CONTROL_TASK__
#define __WATER_CONTROL_TASK__

#include "kernel/Task.h"
#include "model/Greenhouse.h"
#include "tasks/BlinkTask.h"

class WaterControlTask: public Task {

public:
  WaterControlTask(Greenhouse* pGreenhouse, BlinkTask* pBlinkTask); 
  void tick();

private:  
  void setState(int state);
  long elapsedTimeInState();
  //bool isTimeToSample();

  enum { OFF, ON } state;
  long stateTimestamp;

  Greenhouse* pGreenhouse;
  BlinkTask* pBlinkTask;
};

#endif