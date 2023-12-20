#include "Fan.h"
#include "Arduino.h"

Fan::Fan(int pin, int dir1, int dir2) {
    this->pin = pin;
    this->dir1 = dir1;
    this->dir2 = dir2;
    pinMode(pin, OUTPUT);
    isOn = false;
}

void Fan::turnOn() {
    digitalWrite(pin, HIGH);
    isOn = true;
}

void Fan::turnOff() {
    digitalWrite(pin, LOW);
    isOn = false;
}

bool Fan::isFanOn() {
    return isOn;
}