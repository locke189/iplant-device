
#include "JIWifi.h"
#include "JIMqtt.h"

#include "Device.h"
#include "Led.h"
#include "Moisture.h"

////WiFi options
#define SSID "Juan's Wi-Fi Network"            // your network SSID (name)
#define SSID_PWD "Ragnarok189"       // your network password
JIWifi wifi(SSID, SSID_PWD);

////MQTT options
#define MQTT_SERVER "192.168.0.14"
#define MQTT_PORT  1883
#define MQTT_CLIENTID "002"
PubSubClient client(wifi.espClient);
JIMqtt mqtt(MQTT_SERVER, MQTT_PORT, MQTT_CLIENTID, &client);

// Time options
#define   SENSOR_TIME     60000 // 1 minute
unsigned long volatile sensor_timeStamp = 0;

// Device options
#define DEVICE_ID  "1"
#define DEVICE_TYPE "iPlant-prototype"
#define DEVICE_PING_TOPIC "ping"
Device device(DEVICE_ID, DEVICE_TYPE);


// LED 1 options
#define LED1_ID "0"
#define LED1_PIN 2
Led led1(LED1_PIN, HIGH, LED1_ID, DEVICE_ID);

// LED built-in options
#define LEDX_ID "4"
Led led4(LED_BUILTIN, HIGH, LEDX_ID, DEVICE_ID);

// Moisture sensor options
#define MST_ID "0"
#define MST_PIN 0
#define MST_POWER_PIN 9
Moisture moist(MST_PIN, MST_POWER_PIN, MST_ID, DEVICE_ID);


void callback(char* topic, byte* payload, unsigned int length){
//  Serial.println("Callback called...");
//  Serial.print("Message arrived [");
//  Serial.print(topic);
//  Serial.print("] ");
//
//  for (int i=0;i<length;i++) {
//    Serial.print((char)payload[i]);
//  }
//  Serial.println();

  payload[length] = '\0';
  String s = String((char*)payload);


  if(strcmp(topic, led1.getTopic()) == 0){
      
    if(strcmp(s.c_str(), "1") == 0){
      led1.setHigh();
    }else if (strcmp(s.c_str(), "0") == 0){
      led1.setLow();
      }
     mqtt.mqtt_publish(led1.getDataTopic(), String(led1.getState()).c_str() );
      
  } else if(strcmp(topic, led4.getTopic()) == 0){
      Serial.print("Ok!");
      led4.toggle();
      mqtt.mqtt_publish(led4.getDataTopic(), String(led4.getState()).c_str() );
  } else if(strcmp(topic, DEVICE_PING_TOPIC) == 0){
      mqtt.mqtt_publish(device.getRegistrationTopic(), device.getInfo() );
      mqtt.mqtt_publish(device.getActuatorRegistrationTopic(), led1.getInfo() );
      mqtt.mqtt_publish(device.getActuatorRegistrationTopic(), led4.getInfo() );
      mqtt.mqtt_publish(device.getSensorRegistrationTopic(), moist.getInfo() );
  }

  
}

void registration(){
    mqtt.mqtt_publish(device.getRegistrationTopic(), device.getInfo() );
    mqtt.mqtt_publish(device.getActuatorRegistrationTopic(), led1.getInfo() );
    mqtt.mqtt_publish(device.getActuatorRegistrationTopic(), led4.getInfo() );
    mqtt.mqtt_publish(device.getSensorRegistrationTopic(), moist.getInfo() );
  }


void subscriptions(){

    //General
    mqtt.mqtt_subscription(DEVICE_PING_TOPIC);
    //Actuators    
    mqtt.mqtt_subscription(led1.getTopic());
    mqtt.mqtt_subscription(led4.getTopic());
      
  }


void setup(){
  
  // initialize serial for debugging
  Serial.begin(115200);
  // initialize serial for ESP module
  Serial1.begin(115200);
  delay(50);  
  
  //Actuator setup
  led1.setup();
  led4.setup();

  //Sensor setup
  moist.setup();
  
  //Wifi Setup
  wifi.wifi_setup();
  mqtt.mqtt_setup();
  mqtt.mqtt_callback(callback);

  
}

void loop(){

  if (!mqtt.mqtt_connected()) {
    mqtt.mqtt_reconnect();
    registration();
    subscriptions();
   }
  
  mqtt.mqtt_loop(); 



  //Sensor Updates! in main loop
  if ( ((millis() - sensor_timeStamp) >= SENSOR_TIME) || ( ((millis() - sensor_timeStamp) < 0 ) ) ){

    //Send Data to server
    //led1.toggle();
    mqtt.mqtt_publish(moist.getDataTopic(), String(moist.getValue()).c_str() );

    //Reset timestamp 
    sensor_timeStamp = millis();
    }

 
}




