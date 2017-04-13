#include <WiFiEsp.h>
#include <PubSubClient.h>

/*
 WiFiEsp example: WebClient
 This sketch connects to google website using an ESP8266 module to
 perform a simple web search.
 For more details see: http://yaab-arduino.blogspot.com/p/wifiesp-example-client.html
*/


// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(0, 1); // RX, TX
#endif


// Time options
#define   SENSOR_TIME     60000 // 1 minute
unsigned long volatile sensor_timeStamp = 0;

//MQTT options
#define MQTT_SERVER "192.168.0.14"
#define MQTT_PORT  1883

//iPlant Options
#define DEVICE_ID  2
#define LIGHT_SENSOR_ID 4
#define LIGHT_SENSOR_PIN 0
int lightData = 0;

//WiFi options
char ssid[] = "Juan's Wi-Fi Network";            // your network SSID (name)
char pass[] = "Ragnarok189";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status


// Initialize the Ethernet client object
WiFiEspClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;




void setup_wifi() {

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
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
    
    Serial.println("Executing Callback");
    
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i=0;i<length;i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
  

    subscriptions();
    }


void subscriptions(){
      if(client.subscribe("inTopic")){
        Serial.println("Subscription OK");
        }
       else {
        Serial.println("Subscription FAILED");
        }
  }

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected resubscribe
      client.publish("regDevice", "{'id': '2', 'version': '0.1.1', 'type': 'iPlant' }");
      subscriptions();
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void setup()
{
   // set the digital pin as output:

  // initialize serial for debugging
  Serial.begin(115200);
  // initialize serial for ESP module
  Serial1.begin(115200);
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
}



void loop() {

  if (!client.connected()) {
    reconnect();
  }
  
  delay(50);
  client.loop();

  //Sensor Updates! in main loop
  if ( ((millis() - sensor_timeStamp) >= SENSOR_TIME) || ( ((millis() - sensor_timeStamp) < 0 ) ) ){

    //Moisture Sensor Readings
    lightData = analogRead(LIGHT_SENSOR_PIN);    // read the input pin

    
    //Send Data to server
    client.publish("devices/1/sensors/1", String(lightData).c_str());

    
    //Reset timestamp 
    sensor_timeStamp = millis();
    }

}
