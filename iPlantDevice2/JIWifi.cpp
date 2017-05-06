/*
  wifi.cpp - Library for wifi using ESP module without a board.
  Created by Juan Insuasti, April 14, 2017.
*/

#include <WiFiEsp.h>
#include "Arduino.h"
#include "JIWifi.h"

JIWifi::JIWifi(char ssid[], char pass[]){
  _ssid = ssid;
  _pass = pass;
  }

void JIWifi::wifi_setup() {

  delay(10);
  // We start by connecting to a WiFi network
  // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

 // attempt to connect to WiFi network
  while ( _status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(_ssid);
    // Connect to WPA/WPA2 network
    _status = WiFi.begin(_ssid, _pass);
  }
}
