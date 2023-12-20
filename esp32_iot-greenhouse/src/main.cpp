#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

const int soil_pin = 36;
const int dht_pin = 26;

DHT dht11(dht_pin, DHT11);

const char* ssid = "mySSID";
const char* password = "myPassword";

const char *serviceURI = "http://659d-87-10-241-93.ngrok-free.app"; //   http://1e71-87-4-57-200.ngrok-free.app

void connectToWifi(const char* ssid, const char* password){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200); 
  connectToWifi(ssid, password);
  dht11.begin();
}

int sendData(String address, float soilMoisture, float tempC){  
  
   HTTPClient http;
   http.begin(address + "/api/data"); 
   http.addHeader("Content-Type", "application/json");    

   String msg = 
    String("{ \"soilMoisture\": ") + String(soilMoisture) + "," +
    " \"temperature\": " + String(tempC) + " }";
   
   int retCode = http.POST(msg);   
   http.end();  
      
   return retCode;
}

void loop() {
  float soilMoisture;
  int sensor_analog;
  float tempC;
  if (WiFi.status()== WL_CONNECTED){      
    sensor_analog = analogRead(soil_pin);
    soilMoisture = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
    tempC = dht11.readTemperature();
    int code = sendData(serviceURI, soilMoisture, tempC);
    if (code == 200){
       Serial.println("ok " + String(soilMoisture) + " " + String(tempC));   
     } else {
       Serial.println(String("error: ") + code);
     }
    
    delay(5000);

  } else {
    Serial.println("WiFi Disconnected... Reconnect.");
    connectToWifi(ssid, password);
  }
}