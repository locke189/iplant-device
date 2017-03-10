
// Time options
#define   SENSOR_TIME     10000 // 10 seconds

// Wifi Options
#define SSID "Juan's Wi-Fi Network";
#define SSID_PWD "Ragnarok189";
#define SERVER_IP "192.168.0.14"
#define SERVER_PORT "333"

//Time
unsigned long volatile sensor_timeStamp = 0;
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

void setup()  {
  //Serial port setup
  Serial.begin(9600);
  Serial1.begin(115200);
  Serial1.setTimeout(20000);
  delay(10000);

  //ESP module reset
  if (sendData("AT+RST","ready") ) {
    Serial.println("Module is ready");
  } else {
    Serial.println("Module is not ready");
  }
  delay(2000);
  
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
  //Serial.write("AT+CWJAP=\"Juan's Wi-Fi Network\",\"Ragnarok189\"");


  //TCP Server Connection
  cmd = "AT+CIPSTART=\"TCP\",\""; 
  cmd += SERVER_IP; 
  cmd += "\","; 
  cmd += SERVER_PORT;
  
  if (sendData(cmd,"OK")) {
    Serial.println("Connected to server");
  } else {
    Serial.println("Server connection problems");
  }
  delay(2000);  
  //Serial.write("AT+CIPSTART=\"TCP\",\"192.168.0.14\",333");
}

void loop()  {
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

    //Serial1.println("AT");

    //Reset timestamp 
    sensor_timeStamp = millis();
    }
  
}
