#include "UserInput.h"
#include "Arduino.h"
#include "devices/ButtonImpl.h"
#include "config.h"
#include <Wire.h>

UserInput::UserInput(){
  pPumpButton = new ButtonImpl(BTN_WATER_PIN);
  pFanButton = new ButtonImpl(BTN_FAN_PIN);
}

void UserInput::init(){
}

void UserInput::sync(){
  pPumpButton->sync();
  pFanButton->sync();
}

bool UserInput::isPumpButtonPressed(){
  return pPumpButton->isClicked();
}

bool UserInput::isFanButtonPressed(){
  return pFanButton->isClicked();
}