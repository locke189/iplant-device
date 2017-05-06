/*
  JIWifi.cpp - Library for using MQTT protocol with wifi using ESP module without a board.
  Created by Juan Insuasti, April 14, 2017.
*/


// wifi.h must be imported in the main file
#include "JIWifi.h"
#include "JIMqtt.h"
#include "Arduino.h"
#include <PubSubClient.h>

JIMqtt::JIMqtt(char* server, int port, char* clientId, PubSubClient* client){
  strcat(_server, server);
  _port = port;
  _clientId =  clientId;
  _client = client;
  }


void JIMqtt::mqtt_setup(){
    _client->setServer(_server, _port);
    //client.setCallback(callback);
  }



void JIMqtt::mqtt_loop(){

    if (!_client->loop()) {
    Serial.print("Client disconnected...");
    if (_client->connect("arduinoPublisher")) {
      Serial.println("reconnected.");
    } else {
      Serial.println("failed.");
    }
  } 
   delay(100);
}


bool JIMqtt::mqtt_connected(){
    return _client->connected();
  }

void JIMqtt::mqtt_reconnect() {
  Serial.println("MQTT: Reconnecting...");
  // Loop until we're reconnected
  while (!_client->connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    // Attempt to connect
    if (_client->connect(_clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(_client->state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void JIMqtt::mqtt_callback(void (*callback2)(char*, uint8_t*, unsigned int)){
  
   _client->setCallback( (*callback2) );  
}



void JIMqtt::mqtt_subscription(char* topic){
   bool subscribed = false;
   while(!subscribed && _client->connected()){
    subscribed = _client->subscribe(topic,1); 
    }
 
}

void JIMqtt::mqtt_publish(char* topic, char* payload){
  bool published = false;
  while(!published && _client->connected()){
     published = _client->publish(topic, payload);    
    }


  }


