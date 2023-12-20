#include "BTHandler.h"
#include <Arduino.h>
#include "kernel/MsgService.h"
#include "config.h"
#include "kernel/Logger.h"
#include "SoftwareSerial.h"

BTHandler::BTHandler(int rxPin, int txPin) : channel(rxPin, txPin){
}

void BTHandler::init(){
    channel.begin(9600);
}

void BTHandler::sync(){
}

String BTHandler::readMsg(){
    String msg = "";
    while (channel.available()) {
      char letter = (char)channel.read();
      if (letter != '\n') {
        msg.concat(letter);  // Append the character to the buffer
      } else {
        channel.flush();
        return msg;
      }
    }
    return "error - no channel available";
}