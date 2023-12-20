#ifndef __USER_INPUT__
#define __USER_INPUT__

#include "config.h"
#include "devices/Button.h"
#include <Wire.h> 
#include "model/Greenhouse.h"

class UserInput {

public:
  UserInput();

  void init();
  void sync();

  bool isPumpButtonPressed();
  bool isFanButtonPressed();

private:
  Button* pPumpButton;
  Button* pFanButton;
};

#endif
