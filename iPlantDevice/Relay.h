/*
  Relay.h - Library for wifi using ESP module without a board.
  Created by Juan Insuasti, April 14, 2017.
*/

#ifndef Relay_h
#define Relay_h

#include "Arduino.h"
#include "Base.h"

#define RELAY_TYPE "RLY"
#define RELAY_DATA_TOPIC "/data"
#define RELAY_ACTION_TOPIC "/actions"

class Relay: public Base{

  public:
    Relay(int pin, int initialState, char* id, char* deviceId);
    void setup();
    
    void toggle();
    void setHigh();
    void setLow();
    void setState(int state);
    
    int getState();
    char* getDataTopic();
    char* getActionTopic();

  private:
    
    int _state;
    int  _pin;
    char _dataTopic[40];
    char _actionTopic[40];
  };


#endif
