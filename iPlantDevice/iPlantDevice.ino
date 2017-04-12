//iPlant Device
//Rev 28/03/2017
//Version: 0.1.0

// Time options
#define   SENSOR_TIME     60000 // 1 minute
unsigned long volatile sensor_timeStamp = 0;



// Wifi Options
#define SSID "Juan's Wi-Fi Network";
#define SSID_PWD "Ragnarok189";
#define SERVER_IP "192.168.0.12"
#define SERVER_PORT "333"


//Plant Options
#define MOIST_SENSOR_APIN 0
#define MOIST_SENSOR_DPIN 8

//Moisture sensor setup
int moistData = 0;
bool sensorOn = false;

//App Status
bool appConnected = false;

//ESP Functions
String cmd;

bool sendData(String data, char* validation){
  Serial.println(data);  
  Serial1.println(data);

  if (Serial1.find(validation)) {
    Serial1.read();
    return true;
  } else {
    Serial1.read();
    return false;
  }
}

//ESP module reset
void resetModuleESP(){
  if (sendData("AT+RST","ready") ) {
    Serial.println("Module is ready");
  } else {
    Serial.println("Module is not ready");
  }
  delay(2000); 
}

//ESP Wifi Connection
void wifiConnectionESP(){
  //Wifi Connection
  cmd = "AT+CWJAP=\""; 
  cmd += SSID; 
  cmd += "\",\""; 
  cmd += SSID_PWD;
  cmd += "\"";

  if (sendData(cmd,"OK")) {
    Serial.println("WiFi Connected!");
  } else {
    Serial.println("WiFi not ready");
  }
  delay(2000);
}

//ESP Server Connection
bool serverConnectionESP(){
  cmd = "AT+CIPSTART=\"TCP\",\""; 
  cmd += SERVER_IP; 
  cmd += "\","; 
  cmd += SERVER_PORT;
  
  if (sendData(cmd,"OK")) {
    Serial.println("Connected to server");
    delay(2000);
    return true;
  } else {
    Serial.println("Server connection problems");
    delay(2000);
    return false;
  }
  delay(2000);   
}

void setup()  {

  //Moisture sensor setup
  pinMode(MOIST_SENSOR_DPIN, OUTPUT);     // sets the digital pin as output
  digitalWrite(MOIST_SENSOR_DPIN, LOW);    // sets the sensor off
  
  //Serial port setup
  Serial.begin(9600);
  Serial1.begin(115200);
  Serial1.setTimeout(5000);
  delay(10000);

  //ESP module reset
  resetModuleESP();

  //ESP Wifi Connection
  wifiConnectionESP();
  
  //TCP Server Connection
  appConnected = serverConnectionESP();
}

void loop()  {

   if(!appConnected){
     //ESP module reset
     resetModuleESP();
     //ESP Wifi Connection
     wifiConnectionESP();
     //TCP Server Connection
     appConnected = serverConnectionESP();
   }
   
   if (Serial1.available()) {
      int inByte = Serial1.read();
      Serial.write(inByte);
   }
 
  if (Serial.available()) {
     int inByte = Serial.read();
     Serial1.write(inByte);
  }

  //Sensor Updates! in main loop
  if ( ((millis() - sensor_timeStamp) >= SENSOR_TIME) || ( ((millis() - sensor_timeStamp) < 0 ) ) ){

    //Moisture Sensor Readings
    digitalWrite(MOIST_SENSOR_DPIN, HIGH);   // Turns the sensor On
    delay(1000);                  // waits for a second
    moistData = analogRead(MOIST_SENSOR_APIN);    // read the input pin
    delay(1000);
    digitalWrite(MOIST_SENSOR_DPIN, LOW);    // sets the sensor off
    
    //Send Data to server
    
    cmd = "AT+CIPSEND=";
    cmd += String(moistData).length();

    if (sendData(cmd,">") ) {
      Serial.println("Ready to Send");
      if (sendData(String(moistData),"SEND OK") ) {
        Serial.println("Data sent");
        } else {
        Serial.println("Data not sent");
        }
    } else {
      Serial.println("Send command failed");
      appConnected = false;
    }
    delay(1000);
    
    
    //Reset timestamp 
    sensor_timeStamp = millis();
    }
  
}
