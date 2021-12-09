/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

// Import required libraries
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <Wire.h>

#define trigPin D6
#define echoPin D5

float luminosity;
float height;

// Replace with your network credentials
const char* ssid = "SATC IOT";
const char* password = "IOT2021#";

// Set LED GPIO
const int led_R = D3;
const int led_G = D8;
const int led_B = D2;
const int led_extra = D9;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String getHeight() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long timeus = pulseIn(echoPin, HIGH);
  height = 50 - (timeus/58.0);
  //Serial.println(height);
  return String(height);
}
  
String getLuminosity() {
  luminosity = analogRead(A0);
  //Serial.println(luminosity);
  return String(luminosity);
}

// Replaces placeholder with LED state value
String processor(const String& var){
  Serial.println(var);

  if (var == "HEIGHT"){
    return getHeight();
  }
  if (var == "LUMINOSITY"){
    return getLuminosity();
  }  
}
 
void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  pinMode(led_R, OUTPUT);
  pinMode(led_G, OUTPUT);
  pinMode(led_B, OUTPUT);
  pinMode(led_extra, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize SPIFFS
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });

  server.on("/lamp", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/lamp.png", "image/png");
  });

  server.on("/tree", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/tree.png", "image/png");
  });

  server.on("/water", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/water.png", "image/png");
  });

  server.on("/height", HTTP_GET, [](AsyncWebServerRequest *request){
    getHeight();
    if(height > 30) {
      digitalWrite(led_G, HIGH); 
      digitalWrite(led_R, LOW);
    }else {
      digitalWrite(led_G, LOW); 
      digitalWrite(led_R, HIGH);
    }
    request->send_P(200, "text/plain", getHeight().c_str());
  });
  
  server.on("/luminosity", HTTP_GET, [](AsyncWebServerRequest *request){
    getLuminosity();
    if(luminosity > 900) {
      digitalWrite(led_extra, LOW); 
    }else {
      digitalWrite(led_extra, HIGH); 
    }
    request->send_P(200, "text/plain", getLuminosity().c_str());
  });

  server.on("/getWater", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(led_B, HIGH);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  server.on("/stopWater", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(led_B, LOW);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Start server
  server.begin();
}
 
void loop(){
  //digitalWrite(led_B, LOW);
  //delay(30000);
  //digitalWrite(led_B, HIGH);
  //delay(7000);
}
