/*
  Sensor.h - Library for moisture sensor.
  Created by Juan Insuasti, April 14, 2017.
*/

#include "Arduino.h"
#include "Base.h"

void Base::enable(){
  _enabled = true;
  }
void Base::disable(){
  _enabled = false;
  }
  
char* Base::getTopic(){
  return _topic;
  }

void Base::setId(char* id){
  strcpy(_id, id);
  }

void Base::setTopic(char* topic){
  strcpy(_topic, topic);
 }

void Base::setType(char* type){
  strcpy(_type, type);
  }
  
char* Base::getType(){
  return _type;
  }

char* Base::getId(){
  return _id;
  }

bool Base::isEnabled(){
  return _enabled;
  }

void Base::setInfo(){
  _info[0] = 0;
  strcat(_info, "{'id': '");
  strcat(_info, _id);
  strcat(_info, "', 'type': '");
  strcat(_info, _type);
  strcat(_info, "' }");
  }

char* Base::getInfo(){
  return _info;
  } 

void Base::setClass(char* baseClass){
  strcpy(_class, baseClass);
  }
