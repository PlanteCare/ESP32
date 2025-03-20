#include <Arduino.h>
#include "MyMqtt.h"
#include "MyMoistureSensor.h"
#include <WiFi.h>
#include <WiFiManager.h>


#define SERIAL_SPEED 9600
#define MQTT_SERVER "api.lyeshamrani.com"
#define MQTT_PORT 8883
#define MQTT_HUMIDITY_TOPIC "plantecare/humidity"
#define LOOP_DELAY 500
#define MOISTURE_SENSOR_PIN 25
#define MOISTURE_SENSOR_DRY_VALUE 3000
#define MOISTURE_SENSOR_WET_VALUE 1000

#define WIFI_SSID "PlanteCare-AP"
#define WIFI_PASS "PlanteCare"


MyMqtt *myMqtt = nullptr;
MyMoistureSensor *myMoistureSensor = nullptr;
WiFiManager wifiManager;

String moisturePercent;

void setup() {
  Serial.begin(SERIAL_SPEED);
  wifiManager.autoConnect(WIFI_SSID, WIFI_PASS);
  myMqtt = new MyMqtt();
  myMqtt->init(MQTT_SERVER, MQTT_PORT);
  myMqtt->connect();
  myMoistureSensor = new MyMoistureSensor();
  myMoistureSensor->init(MOISTURE_SENSOR_PIN, MOISTURE_SENSOR_DRY_VALUE, MOISTURE_SENSOR_WET_VALUE);
}

void loop() {
  moisturePercent = myMoistureSensor->getMoisture();
  myMqtt->publish(MQTT_HUMIDITY_TOPIC, moisturePercent.c_str());
  myMqtt->loop();
  delay(LOOP_DELAY);  
}

