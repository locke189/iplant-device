/*
  Led.h - Library for wifi using ESP module without a board.
  Created by Juan Insuasti, April 14, 2017.
*/

#ifndef Led_h
#define Led_h

#include "Arduino.h"
#include "Base.h"

#define LED_TYPE "LED"
#define LED_DATA_TOPIC "/data"
#define LED_ACTION_TOPIC "/actions"

class Led: public Base{

  public:
    Led(int pin, int initialState, char* id, char* deviceId);
    void setup();
    
    void toggle();
    void setHigh();
    void setLow();
    void setState(int state);
    
    int getState();
    char* getDataTopic();
    char* getActionTopic();

  private:
    
    int _ledState;
    int  _ledPin;
    char _dataTopic[40];
    char _actionTopic[40];
  };


#endif
