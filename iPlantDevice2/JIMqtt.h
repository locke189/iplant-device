/*
  JIWifi.cpp - Library for using MQTT protocol with wifi using ESP module without a board.
  Created by Juan Insuasti, April 14, 2017.
*/

#ifndef JIMqtt_h
#define JIMqtt_h

// wifi.h must be imported in the main file
#include "JIWifi.h"
#include "Arduino.h"
#include <PubSubClient.h>

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(0, 1); // RX, TX
#endif


class JIMqtt{

  public:
    JIMqtt(char* server, int port, char* clientId, PubSubClient* client);
    void mqtt_setup();
    bool mqtt_connected();
    void mqtt_publish(char* topic, char* payload);
    void mqtt_reconnect();
    void mqtt_subscription(char* topic);
    void mqtt_loop();
    void mqtt_callback(void (*callback2)(char*, uint8_t*, unsigned int));
  
  private:
    char _server[16];
    int _port;
    int _value;
    String _clientId;
    PubSubClient* _client;

  };




#endif
