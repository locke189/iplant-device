#ifndef Shared_h
#define Shared_h

#include <string.h>
#include "Arduino.h"

//Component type
#define SENSOR true
#define ACTUATOR false

//Component type
#define ENABLED true
#define DISABLED false

//Component type
#define DIGITAL true
#define ANALOG false

//Sensors
#define MST 0
#define LIG 1

//Actuators
#define LED 50
#define RLY 51

//Actuator Actions
#define A_OFF "0"
#define A_ON  "1"
#define A_TOGGLE "2" 


struct Component {
  byte deviceId;
  byte id;
  bool componentType;  // ACTUATOR / SENSOR
  byte type;
  int data;
  bool enabled;
  int pin;
  bool digital;
};



char* getType(byte type){
  
    switch (type) {
        // SENSORS
        case MST:
          return "MST";
          break;
        case LIG:
          return "LIG";
          break;
        // ACTUATORS
        case LED:
          return "LED";
          break;
        case RLY:
          return "RLY";
          break;           
        default: 
          return "NAN";
        break;
      }
  
  }


void readData(Component *component){
    if (component->enabled){
      if(component->digital == DIGITAL){
        component->data = digitalRead(component->pin);
        }
      else {
        component->data = analogRead(component->pin);
        }
    }
}

void writeData(Component *component, int data){
    if (component->enabled){
      component->data = data;
      if(component->digital == DIGITAL){
        digitalWrite(component->pin, data);
        }
      else {
        analogWrite(component->pin, data);
        }
    }
}

void toggleData(Component *component){
    if (component->enabled){
      if(component->digital){
          if (component->data == LOW) {
            component->data = HIGH;
          } else {
            component->data = LOW;
          }
          digitalWrite(component->pin, component->data);
        }
    }
}

void setComponent( Component *component , byte deviceId, byte id, bool componentType, byte type, bool enabled, int pin, bool digital, int data){
  component->deviceId = deviceId;
  component->id = id;
  component->componentType = componentType;  // ACTUATOR / SENSOR
  component->type = type ;
  component->enabled = enabled;
  component->pin = pin;
  component->digital = digital;

  if(component->componentType == SENSOR){
    if(component->digital == DIGITAL){
      pinMode(component->pin , INPUT);
    }
    readData(component);
    }
  else{
    pinMode(component->pin , OUTPUT);
    writeData(component, data);
    }
  }



  
#endif
