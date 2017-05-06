/*
  Led.cpp - Library for LED Actuator... just a led..
  Created by Juan Insuasti, April 14, 2017.
*/

#include "Arduino.h"
#include "Relay.h"

Relay::Relay(int pin, int initialState, char id[3], char deviceId[3]){
  _pin = pin;
  _state = initialState;
  char tempTopic[40] = "/devices/";
  strcat(tempTopic, deviceId);
  strcat(tempTopic, "/actuators/");
  strcat(tempTopic, id);

  setTopic( tempTopic );
  setId( id );
  setType( RELAY_TYPE );
  setClass( ACTUATOR );
  setInfo();
  strcat( _dataTopic, getTopic() );
  strcat( _dataTopic, RELAY_DATA_TOPIC );
  }
    
void Relay::toggle(){
    // if the Relay is off turn it on and vice-versa:
    if (_state == LOW) {
      _state = HIGH;
    } else {
      _state = LOW;
    }
    digitalWrite(_pin, _state);
  }

void Relay::setup(){
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, _state);
  }

// Relay has negated logic
void Relay::setHigh(){
  _state = LOW;
  digitalWrite(_pin, _state);
  }

void Relay::setLow(){
  _state = HIGH;
  digitalWrite(_pin, _state);
  }

void Relay::setState(int state){
  _state = state;
  digitalWrite(_pin, _state);
  }

int Relay::getState(){
  return _state;
  }

 char* Relay::getDataTopic(){
  return _dataTopic;
  
  }

   char* Relay::getActionTopic(){
  return _actionTopic;
  
  }
