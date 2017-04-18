/*
  Device.h - device main functions.
  Created by Juan Insuasti, April 14, 2017.
*/

#ifndef Device_h
#define Device_h

#include "Arduino.h"
#include "Base.h"

#define DEV_REGISTER_SUFFIX "regDevice"
#define DEV_SENSOR_REGISTER_SUFFIX "/regSensor"
#define DEV_ACTUATOR_REGISTER_SUFFIX "/regActuator"

class Device: public Base{

  public:
    Device(char* id, char* type );

    void setTopics();
    
    char* getRegistrationTopic();
    char* getSensorRegistrationTopic();
    char* getActuatorRegistrationTopic();

  private:
    char _regTopic[30];
    char _regSenTopic[30];
    char _regActTopic[30];

  };

  #endif
