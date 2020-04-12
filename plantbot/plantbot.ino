/*
  Acknowledgment of code on HTTP POSTing:
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp32-http-get-post-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  Everything else @mrpjevans
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Settings
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* serverName = "http://<YOUR_INFLUXDB_IP_ADDRESS>:8086/write?db=plantbot";

// Set up
int sensorPin = A0;
int sensorValue = 0;
int delayTime = 30000;

void connectToWiFi() {
  // Connect to WiFi
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());  
}

void sendToInflux(int moisture) {
  
  HTTPClient http;    
  http.begin(serverName);

  String httpRequestData = "succ1 moisture=" + String(moisture);

  Serial.println("Sending notification");
  int httpResponseCode = http.POST(httpRequestData);
      
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);
        
  http.end();

}

void setup() {
  Serial.begin(115200);
  Serial.println("Plantbot!");
  connectToWiFi();
}

void loop() {

  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);

  //Check WiFi connection status
  if (WiFi.status() != WL_CONNECTED) {
      connectToWiFi();
  }

  sendToInflux(sensorValue);
  
  delay(delayTime);

}
