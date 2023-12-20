#include "WaterPump.h"
#include "Arduino.h"

WaterPump::WaterPump(int relayPin) {
    this->relayPin = relayPin;
    pinMode(relayPin, OUTPUT);
    isOn = false;
}

void WaterPump::turnOn() {
    digitalWrite(relayPin, LOW);
    isOn = true;
}

void WaterPump::turnOff() {
    digitalWrite(relayPin, HIGH);
    isOn = false;
}

bool WaterPump::isPumpOn() {
    return isOn;
}