#ifndef Protocol_h
#define Protocol_h

#include <string.h>
#include "Arduino.h"


//Discovery
#define DEV_REGISTER_SUFFIX "regDevice"
#define DEV_SENSOR_REGISTER_SUFFIX "/regSensor"
#define DEV_ACTUATOR_REGISTER_SUFFIX "/regActuator"

//Global Variables
char _topic[40];
char _message[80];

void setComponentTopic(Component *component){
  
  strcpy(_topic, "/devices/");
  strcat(_topic, String(int(component->deviceId)).c_str());
  if(component->componentType == SENSOR){
    strcat(_topic, "/sensors/");
    }
  else {
    strcat(_topic, "/actuators/");
    }
  strcat(_topic, String(int(component->id)).c_str());
  }


void setComponentDataTopic(Component *component){
  setComponentTopic(component);
  strcat(_topic, "/data");
  }

void setComponentInfo(Component *component){
  strcpy(_message, "{'id':'");
  strcat(_message, String(int(component->id)).c_str() );
  strcat(_message, "','type':'");
  strcat(_message, getType(component->type));
  strcat(_message, "','data':'");
  strcat(_message, String(component->data).c_str());
  strcat(_message, "','enabled':'");

  if(component->enabled){
    strcat(_message, "true");
    }
  else{
    strcat(_message, "false");
    }
  strcat(_message, "'}");
  }

void setDeviceInfo(byte *deviceId, char *deviceType){
  strcpy(_message, "{'id':'");
  strcat(_message, String(int(deviceId )).c_str());
  strcat(_message, "','type':'");
  strcat(_message, deviceType);
  strcat(_message, "'}");

  }



void setDeviceTopic(byte deviceId){
  strcpy(_topic, "/devices/");
  strcat(_topic, String(int(deviceId )).c_str());
  }

void setSensorRegisterTopic(byte deviceId){
  setDeviceTopic(deviceId);
  strcat(_topic, DEV_SENSOR_REGISTER_SUFFIX);
  }

void setActuatorRegisterTopic(byte deviceId){
  setDeviceTopic(deviceId);
  strcat(_topic, DEV_ACTUATOR_REGISTER_SUFFIX);
  }

char* getMessage(){
  return _message;
  }

char* getTopic(){
  return _topic;
  }


#endif
