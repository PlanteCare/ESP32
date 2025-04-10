/**
 * Classe controleur pour un pot de fleurs intelligent (PlanteCare)
 * @file MyPlanteCare.cpp
 * @name MyPlanteCare
 * @brief Declaration des méthodes de la classe controleur MyPlanteCare
 *
 * @authors Lyes Hamrani
 * @version 1.0
 * @date Création : 28/03/2025
 * @date Dernière mise à jour : 28/03/2025
 */
#include "MyPlanteCare.h"

MyPlanteCare::MyPlanteCare(planteCareConfig *_config)
{
    if (_config != nullptr)
    {
        this->config = *_config;
    }
}

MyPlanteCare::~MyPlanteCare()
{
    delete myMqtt;
    delete myOled;
    delete myMofset;
    delete myMoistureSensor;
    delete myWaterSensor;
    delete redLed;
    delete greenLed;
    delete witheLed;
}

bool MyPlanteCare::init()
{
    if (!setupLeds() || redLed == nullptr || greenLed == nullptr || witheLed == nullptr)
    {
        Serial.println("Erreur lors de la configuration des LEDs.");
        return false;
    }
    witheLed->on();
    if (!setupOled() || myOled == nullptr)
    {
        Serial.println("Erreur lors de la configuration de l'OLED.");
        redLed->on();
        return false;
    }
    greenLed->blink();
    if (!setupWifi())
    {
        Serial.println("Erreur lors de la configuration du WiFi.");
        redLed->on();
        return false;
    }
    {
        Serial.println("Erreur lors de la configuration du WiFi.");
        redLed->on();
        return false;
    }
    greenLed->blink();
    if (!setupMqtt() || myMqtt == nullptr)
    {
        Serial.println("Erreur lors de la configuration du MQTT.");
        redLed->on();
        return false;
    }
    {
        Serial.println("Erreur lors de la configuration du MQTT.");
        redLed->on();
        return false;
    }
    greenLed->blink();
    if (!setupMofset() || myMofset == nullptr)
    {
        Serial.println("Erreur lors de la configuration du Mofset.");
        redLed->on();
        myMqtt->publish(config.mqttTopic, "Erreur Mofset.");
        return false;
    }
    greenLed->blink();
    return true;
}

bool MyPlanteCare::setupLeds()
{
    redLed = new MyLed(config.redLedPin, config.ledsBlinkDelay);
    greenLed = new MyLed(config.greenLedPin, config.ledsBlinkDelay);
    witheLed = new MyLed(config.witheLedPin, config.ledsBlinkDelay);

    if (!redLed->init())
    {
        Serial.println("Erreur lors de la configuration de la LED rouge.");
        return false;
    }
    if (!greenLed->init())
    {
        Serial.println("Erreur lors de la configuration de la LED verte.");
        return false;
    }
    if (!witheLed->init())
    {
        Serial.println("Erreur lors de la configuration de la LED blanche.");
        return false;
    }
    redLed->blink();
    witheLed->blink();
    greenLed->blink();
    return true;
}

bool MyPlanteCare::setupOled()
{
    Serial.println("Initialisation de l'OLED...");
    myOled = new MyOled(&Wire, config.oledResPin, config.oledHeight, config.oledWidth);
    myOled->init(config.oledSplashDelay);
    myOled->clearDisplay();
    return true;
}

bool MyPlanteCare::setupWifi()
{
    Serial.println("Initialisation de la connexion WiFi...");
    myOled->printIt(10, 2, "CONFIGURATION...", true);
    myOled->printIt(2, 20, "Se connecter au WiFi:", true);
    myOled->printIt(15, 30, "SSID: ", false);
    myOled->printIt(50, 30, config.ssid, true);
    myOled->printIt(15, 40, "PASS: ", false);
    myOled->printIt(50, 40, config.password, true);

    wifiManager.setTimeout(config.wifiTimeout);
    wifiManager.setConfigPortalTimeout(config.wifiPortalTimeout);

    bool connected = wifiManager.autoConnect(config.ssid, config.password);
    if (connected)
    {
        Serial.println("Connecté au WiFi !");
        myOled->clearDisplay();
        myOled->printIt(10, 2, "WIFI CONNECTE", true);
        myOled->printIt(10, 30, WiFi.SSID().c_str(), true);
        return true;
    }
    else
    {
        Serial.println("Échec de la connexion WiFi");
        myOled->clearDisplay();
        myOled->printIt(10, 2, "ERREUR WIFI", true);
        myOled->printIt(10, 30, "Echec de connexion", true);
        return false;
    }
    delay(config.setupDelay);
}

bool MyPlanteCare::setupMqtt()
{
  Serial.println("Initialisation de la connexion MQTT...");
  myOled->clearDisplay();
  myOled->printIt(10, 2, "CONFIGURATION...", true);
  myOled->printIt(10, 30, "Connexion MQTT...", true);
  myMqtt = new MyMqtt(config.mqttServer, config.mqttPort);
  myMqtt->init();
  if (myMqtt->connect()) {
    myOled->clearDisplay();
    myOled->printIt(10, 2, "MQTT CONNECTE", true);
    myOled->printIt(10, 30, "Connexion reussie", true);
    return true;
  } else {
    myOled->clearDisplay();
    myOled->printIt(10, 2, "ERREUR MQTT", true);
    myOled->printIt(10, 30, "Echec de connexion", true);
    return false;
  }
  delay(config.setupDelay);
  return true;
}

bool MyPlanteCare::setupMofset()
{
    Serial.println("Initialisation du Mofset...");
    myOled->clearDisplay();
    myOled->printIt(10, 2, "CONFIGURATION...", true);
    myOled->printIt(15, 30, "Mofset...", true);
    myOled->printIt(10, 40, "Pin: ", false);
    myOled->printIt(50, 40, String(config.mofsetPin).c_str(), true);
    myMofset = new MyMofset(config.mofsetPin);
    if (!myMofset->init())
    {
        Serial.println("Erreur lors de la configuration du Mofset.");
        myOled->clearDisplay();
        myOled->printIt(10, 2, "ERREUR MOFSET", true);
        myOled->printIt(50, 30, "Echec initialisation", true);
        return false;
    }
    delay(config.setupDelay);
    return true;
}

