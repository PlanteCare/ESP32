#include <Arduino.h>
#include "MyPlanteCare.h"

#define SERIAL_SPEED 9600
#define SERIAL_DELAY 1000
#define LOOP_DELAY 500

// Configuration pour le test
#define GREEN_LED_PIN 16
#define WHITE_LED_PIN 17
#define RED_LED_PIN 18
#define LEDS_BLINK_DELAY 300

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4
#define SPLASH_TIME 1200

// WiFi
#define WIFI_SSID "PlanteCare"
#define WIFI_PASS "Secure1234"
#define WIFI_TIMEOUT 180
#define WIFI_PORTAL_TIMEOUT 120

// MQTT
#define MQTT_SERVER "api.lyeshamrani.com"
#define MQTT_PORT 8883

// MOFSET
#define MOFSET_PIN 2

// Capteur d'eau
#define WATER_SENSOR_PIN 36
#define WATER_MAX_VALUE 1500
#define WATER_MIN_VALUE 0

// Capteur d'humidité
#define MOISTURE_SENSOR_PIN 35
#define MOISTURE_MAX_VALUE 3000
#define MOISTURE_MIN_VALUE 1000

// COMPONENTS SETUP DELAY
#define SETUP_DELAY 1000
#define LOOP_DELAY_VALUE 2000
#define MOSFET_DELAY 5000

// Déclaration du contrôleur global
MyPlanteCare *planteCare = nullptr;

void setup()
{
  Serial.begin(SERIAL_SPEED);
  Serial.println("Démarrage du PlanteCare...");
  delay(SERIAL_DELAY);
  
  // Création de la configuration pour le test
  planteCareConfig config;
  
  // Configuration minimale pour le test (LEDs et OLED)
  config.setupDelay = SETUP_DELAY;
  config.redLedPin = RED_LED_PIN;
  config.greenLedPin = GREEN_LED_PIN;
  config.witheLedPin = WHITE_LED_PIN;
  config.ledsBlinkDelay = LEDS_BLINK_DELAY;
  config.oledWidth = SCREEN_WIDTH;
  config.oledHeight = SCREEN_HEIGHT;
  config.oledResPin = OLED_RESET;
  config.oledSplashDelay = SPLASH_TIME;
  config.ssid = WIFI_SSID;
  config.password = WIFI_PASS;
  config.wifiTimeout = WIFI_TIMEOUT;
  config.wifiPortalTimeout = WIFI_PORTAL_TIMEOUT;
  config.mqttServer = MQTT_SERVER;
  config.mqttPort = MQTT_PORT;
  config.mofsetPin = MOFSET_PIN;
  config.waterSensorPin = WATER_SENSOR_PIN;
  config.waterMaxValue = WATER_MAX_VALUE;
  config.waterMinValue = WATER_MIN_VALUE;
  config.moistureSensorPin = MOISTURE_SENSOR_PIN;
  config.moistureWetValue = MOISTURE_MAX_VALUE;
  config.moistureDryValue = MOISTURE_MIN_VALUE;
  config.loopDelay = LOOP_DELAY_VALUE;
  config.mosfetDelay = MOSFET_DELAY;
  
  // Création et initialisation du contrôleur
  planteCare = new MyPlanteCare(&config);
  
  if (!planteCare->init()) {
    Serial.println("Erreur lors de l'initialisation du PlanteCare");
  } else {
    Serial.println("PlanteCare initialisé avec succès!");
  }
}

void loop()
{
  planteCare->getValues();
  delay(LOOP_DELAY);
}