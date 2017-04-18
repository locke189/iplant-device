/*
  Led.cpp - Library for LED Actuator... just a led..
  Created by Juan Insuasti, April 14, 2017.
*/

#include "Arduino.h"
#include "Led.h"

Led::Led(int pin, int initialState, char* id, char* deviceId){
  _ledPin = pin;
  _ledState = initialState;
  char tempTopic[40] = "devices/";
  strcat(tempTopic, deviceId);
  strcat(tempTopic, "/actuators/");
  strcat(tempTopic, id);

  setTopic( tempTopic );
  setId( id );
  setType( LED_TYPE );
  setClass( ACTUATOR );
  setInfo();
    strcat( _dataTopic, getTopic() );
  strcat( _dataTopic, LED_DATA_TOPIC );
  }
    
void Led::toggle(){
    // if the LED is off turn it on and vice-versa:
    if (_ledState == LOW) {
      _ledState = HIGH;
    } else {
      _ledState = LOW;
    }
    digitalWrite(_ledPin, _ledState);
  }

void Led::setup(){
    pinMode(_ledPin, OUTPUT);
    digitalWrite(_ledPin, _ledState);
  }

void Led::setHigh(){
  _ledState = HIGH;
  digitalWrite(_ledPin, _ledState);
  }

void Led::setLow(){
  _ledState = LOW;
  digitalWrite(_ledPin, _ledState);
  }

void Led::setState(int state){
  _ledState = state;
  digitalWrite(_ledPin, _ledState);
  }

int Led::getState(){
  return _ledState;
  }

 char* Led::getDataTopic(){
  return _dataTopic;
  
  }
