
#include "JIWifi.h"
#include "JIMqtt.h"

#include "shared.h"
#include "protocol.h"

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
#define DEVICE_ID  1
#define DEVICE_TYPE "iPlant-prototype"
#define DEVICE_PING_TOPIC "ping"


// RELAY 1 options
#define RELAY1_ID  0
#define RELAY1_PIN 2
Component relay1;

// LED built-in options
#define LEDX_ID 4
Component led4;

// Moisture sensor options
#define MST_ID 0
#define MST_PIN 0
#define MST_POWER_PIN 9
Component moist1;


void callback(char* topic, byte* payload, unsigned int length){

  Serial.println("Callback called...");
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");


  payload[length] = '\0';
  String s = String((char*)payload);

//RELAY callback actions
  setComponentTopic(&relay1);
  if(strcmp(topic, getTopic() ) == 0){
      
    if(strcmp(s.c_str(), A_ON) == 0){
      writeData(&relay1, LOW);
    }else if (strcmp(s.c_str(), A_OFF) == 0){
      writeData(&relay1, HIGH);
      }
      
     //Device return message to 
     setComponentDataTopic(&relay1);
     mqtt.mqtt_publish(getTopic(), String(relay1.data).c_str() );
      
  }

//LED Callback Actions
  setComponentTopic(&led4);
  if(strcmp(topic, getTopic()) == 0){

    if(strcmp(s.c_str(), A_ON) == 0){
      writeData(&led4, HIGH);
     }
     else if (strcmp(s.c_str(), A_OFF) == 0){
      writeData(&led4, LOW);
     }
     else if (strcmp(s.c_str(), A_TOGGLE) == 0){
      toggleData(&led4);     
     }
      
      setComponentDataTopic(&led4);
      mqtt.mqtt_publish(getTopic(), String(led4.data).c_str());
  } 

//PING Callback Actions
  if(strcmp(topic, DEVICE_PING_TOPIC) == 0){
      registration();
  }

  
}

void registration(){
    //registering device
    setDeviceInfo(DEVICE_ID, DEVICE_TYPE);
    mqtt.mqtt_publish( DEV_REGISTER_SUFFIX, getMessage() );
    delay(200);

    //registering actuator: relay1
    setActuatorRegisterTopic(DEVICE_ID);
    setComponentInfo(&relay1);
    mqtt.mqtt_publish(getTopic(), getMessage());
    delay(200);
    
    //registering actuator: led4
    setActuatorRegisterTopic(DEVICE_ID);
    setComponentInfo(&led4);
    mqtt.mqtt_publish(getTopic(), getMessage());
    delay(200);

    //registering sensor: moist1
    setSensorRegisterTopic(DEVICE_ID);
    setComponentInfo(&moist1);
    mqtt.mqtt_publish(getTopic(), getMessage() );
  }


void subscriptions(){

    //General
    Serial.print("Subscription [");
    Serial.print(DEVICE_PING_TOPIC);
    Serial.print("] ");
    mqtt.mqtt_subscription(DEVICE_PING_TOPIC);
    //Actuators
    setComponentTopic(&relay1);
    Serial.print("Subscription [");
    Serial.print(getTopic());
    Serial.print("] ");
    mqtt.mqtt_subscription(getTopic());
    setComponentTopic(&led4);
    Serial.print("Subscription [");
    Serial.print(getTopic());
    Serial.print("] ");
    mqtt.mqtt_subscription(getTopic());
  }


void setup(){
  
  // initialize serial for debugging
  Serial.begin(115200);
  // initialize serial for ESP module
  Serial1.begin(115200);
  delay(50);  
  
  //Actuator setup
  //set Component Signature Component *component , byte deviceId, byte id, bool componentType, byte type, bool enabled, int pin, bool digital, int data
  setComponent(&relay1, DEVICE_ID, RELAY1_ID, ACTUATOR, RLY, ENABLED, RELAY1_PIN, DIGITAL, HIGH);
  setComponent(&led4, DEVICE_ID, LEDX_ID, ACTUATOR, LED, ENABLED, LED_BUILTIN, DIGITAL, HIGH);

  //Sensor setup
 setComponent(&moist1, DEVICE_ID, MST_ID, SENSOR, MST, ENABLED, MST_PIN, ANALOG, HIGH);
  
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
    setComponentDataTopic(&moist1);
    readData(&moist1);
    delay(50);
    mqtt.mqtt_publish(getTopic(), String(moist1.data).c_str() );

    //Reset timestamp 
    sensor_timeStamp = millis();
    }

 
}




