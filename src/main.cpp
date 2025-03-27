#include <Arduino.h>
#include "MyMqtt.h"
#include "MyMoistureSensor.h"
#include <WiFi.h>
#include <WiFiManager.h>
#include "MyOled.h"

#define SERIAL_SPEED 9600
#define MQTT_SERVER "api.lyeshamrani.com"
#define MQTT_PORT 8883
#define MQTT_HUMIDITY_TOPIC "plantecare/humidity"
#define LOOP_DELAY 500
#define SERIAL_DELAY 300
#define MOISTURE_SENSOR_PIN 25
#define MOISTURE_SENSOR_DRY_VALUE 3000
#define MOISTURE_SENSOR_WET_VALUE 1000
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET 4     
#define SPLASH_TIME 1200 

#define WIFI_SSID "PlanteCare-AP"
#define WIFI_PASS "PlanteCare"

MyMqtt *myMqtt = NULL;
MyMoistureSensor *myMoistureSensor = NULL;
MyOled *myOled = NULL;
WiFiManager wifiManager;


void setup() {
  Serial.begin(SERIAL_SPEED);
  delay(SERIAL_DELAY);
  myOled = new MyOled(&Wire, OLED_RESET, SCREEN_HEIGHT, SCREEN_WIDTH);
  myOled->init(SPLASH_TIME);
}

void loop() {
  delay(LOOP_DELAY);
}