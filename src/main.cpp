#include <Arduino.h>
#include "MyMqtt.h"
#include <WiFi.h>
#include <WiFiManager.h>


#define SERIAL_SPEED 9600
#define MQTT_SERVER "api.lyeshamrani.com"
#define MQTT_PORT 8883
#define MQTT_TOPIC "plantecare/message"
#define LOOP_DELAY 60000

#define WIFI_SSID "PlanteCare-AP"
#define WIFI_PASS "PlanteCare"


MyMqtt *myMqtt = nullptr;
WiFiManager wifiManager;

void setup() {
  Serial.begin(SERIAL_SPEED);
  Serial.println("Booting...");
  bool res = wifiManager.autoConnect(WIFI_SSID, WIFI_PASS);
  if (!res) {
    Serial.println("Échec de connexion au WiFi");
    ESP.restart();
  } else {
    Serial.println("Connecté au WiFi");
  }
  myMqtt = new MyMqtt();
  myMqtt->init(MQTT_SERVER, MQTT_PORT);
  myMqtt->connect();
}

void loop() {
  myMqtt->publish(MQTT_TOPIC, "Hello from ESP32");
  myMqtt->loop();
  delay(LOOP_DELAY);  
}

