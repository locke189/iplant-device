/*
  Device.h - device main functions.
  Created by Juan Insuasti, April 14, 2017.
*/

#include "Arduino.h"
#include "Device.h"


Device::Device(char* id, char* type ){
  char tempTopic[30] = "/devices/";
  strcat(tempTopic, id );
  setTopic( tempTopic );
  setId( id );
  setType( type );
  setClass( DEVICE );
  setInfo();
  setTopics();
  }

void Device::setTopics(){
  _regTopic[0] = 0;
  strcat(_regTopic, DEV_REGISTER_SUFFIX);
  _regSenTopic[0] = 0;
  strcat(_regSenTopic, getTopic());
  strcat(_regSenTopic, DEV_SENSOR_REGISTER_SUFFIX);
  _regActTopic[0] = 0;
  strcat(_regActTopic, getTopic());
  strcat(_regActTopic, DEV_ACTUATOR_REGISTER_SUFFIX);
  }

char* Device::getRegistrationTopic(){
  return _regTopic;
  }
  
char* Device::getSensorRegistrationTopic(){
  return _regSenTopic;
  }
  
char* Device::getActuatorRegistrationTopic(){

  return _regActTopic;
  }
