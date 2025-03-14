#include <Arduino.h>
#include "MyMqtt.h"
#include "MyWifi.h"


#define SERIAL_SPEED 9600
#define MQTT_SERVER "lyeshamrani.com"
#define MQTT_PORT 1883
#define WIFI_SSID "GIGACHAD"
#define WIFI_PASSWORD "BigNoobs999"
#define MQTT_TOPIC "plantecare/message"
#define LOOP_DELAY 60000

MyMqtt *myMqtt = nullptr;
MyWifi *myWifi = nullptr;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_SPEED);
  myWifi = new MyWifi();
  myWifi->init(WIFI_SSID, WIFI_PASSWORD);
  myWifi->connect();
  myMqtt = new MyMqtt();
  myMqtt->init(MQTT_SERVER, MQTT_PORT);
  myMqtt->connect();
}

void loop() {
  myMqtt->publish(MQTT_TOPIC, "Hello from ESP32");
  myMqtt->loop();
  delay(LOOP_DELAY);  
}

