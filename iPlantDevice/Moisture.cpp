/*
  Moisture.h - Library for moisture sensor.
  Created by Juan Insuasti, April 14, 2017.
*/

#include "Arduino.h"
#include "Moisture.h"


Moisture::Moisture(int pin, int powerPin, char* id, char* deviceId){
  _powerPin = powerPin;
  _sensorPin = pin;

  char tempTopic[40] = "devices/";
  strcat(tempTopic, deviceId);
  strcat(tempTopic, "/sensors/");
  strcat(tempTopic, id);
  setTopic( tempTopic );
  setId( id );
  setType( MST_TYPE );
  setClass( SENSOR );
  setInfo();
  strcat( _dataTopic, getTopic() );
  strcat( _dataTopic, MST_DATA_TOPIC );
  }
    

void Moisture::setup(){
    disable();
    pinMode(_powerPin, OUTPUT);
    digitalWrite(_powerPin, isEnabled() );
  }


int Moisture::getValue(){
  enable();
  digitalWrite(_powerPin, isEnabled() );
  delay(500);
  _value = analogRead(_sensorPin);    // read the input pin;
  disable();
  digitalWrite(_powerPin, isEnabled() );
  return _value;
  }

 char* Moisture::getDataTopic(){
  return _dataTopic;
  
  }
