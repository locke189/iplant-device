/*
  Base.h - base class for sensors/actuators.
  Created by Juan Insuasti, April 14, 2017.
*/

#ifndef Base_h
#define Base_h

#include <string.h>
#include "Arduino.h"

#define DATA_SUFFIX "/data"
#define OPTIONS_SUFFIX "/actions"
#define DEVICE "DEV"
#define SENSOR "SEN"
#define ACTUATOR "ACT"

class Base{

  public:
    void enable();
    void disable();
    void setClass(char* baseClass);
    void setId(char* id);
    void setTopic(char* topic);
    void setType(char* type);
    void setInfo();

    bool isEnabled();
    char* getInfo();
    char* getType();
    char* getId();
    char* getTopic();


  protected:
    bool _enabled;
    char _class[4];
    char _id[3]; 
    char _type[20];
    char _info[50];
    char _topic[40];


  };


#endif
