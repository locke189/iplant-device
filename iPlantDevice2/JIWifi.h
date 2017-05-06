/*
  wifi.cpp - Library for wifi using ESP module without a board.
  Created by Juan Insuasti, April 14, 2017.
*/

#ifndef JIWifi_h
#define JIWifi_h

#include <WiFiEsp.h>
#include "Arduino.h"

class JIWifi{

  public:
    JIWifi(char ssid[], char pass[]);
    void wifi_setup();
    WiFiEspClient espClient;
    
  private:
    int _status = WL_IDLE_STATUS;     // the Wifi radio's status
    char* _ssid;        // your network SSID (name)
    char* _pass;        // your network password
  };

#endif
