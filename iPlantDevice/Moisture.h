/*
  Moisture.h - Library for moisture sensor.
  Created by Juan Insuasti, April 14, 2017.
*/

#ifndef Moisture_h
#define Moisture_h

#include "Arduino.h"
#include "Base.h"

#define MST_TYPE "MST"
#define MST_DATA_TOPIC "/data"

class Moisture: public Base {
//class Moisture {
  public:
    Moisture(int pin, int powerPin, char* id, char* deviceId);
    void setup();
    
    int  getValue();
    char* getDataTopic();

  private:
    int  _powerPin;
    int  _sensorPin;
    int _value;
    char _dataTopic[40];
  };





#endif
