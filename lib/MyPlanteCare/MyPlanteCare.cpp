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
    greenLed->blink();
    if (!setupMqtt() || myMqtt == nullptr)
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
        return false;
    }
    greenLed->blink();
    if (!setupMoistureSensor() || myMoistureSensor == nullptr)
    {
        Serial.println("Erreur lors de la configuration du capteur d'humidité.");
        redLed->on();
        return false;
    }
    greenLed->blink();
    if (!setupWaterSensor() || myWaterSensor == nullptr)
    {
        Serial.println("Erreur lors de la configuration du capteur d'eau.");
        redLed->on();
        return false;
    }
    greenLed->blink();

    statusDoc["status"] = "OK";
    statusDoc["moisture"] = "OK";
    statusDoc["water"] = "OK";
    statusDoc["wifi"] = "OK";
    statusDoc["mqtt"] = "OK";
    statusDoc["mofset"] = "OK";
    statusDoc["leds"] = "OK";
    statusDoc["oled"] = "OK";

    serializeJson(statusDoc, jsonBuffer);

    myMqtt->publish("plantecare/status", jsonBuffer);
    
    witheLed->off();
    greenLed->on();

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
    if (myOled->init(config.oledSplashDelay) != 0) {
        Serial.println("Erreur lors de l'initialisation de l'OLED");
        return false;
    }
    myOled->clearDisplay();
    myOled->setTextSize(1);
    return true;
}

bool MyPlanteCare::setupWifi()
{
    Serial.println("Initialisation de la connexion WiFi...");
    
    myOled->clearDisplay();
    myOled->drawRect(0, 0, 128, 12, SSD1306_WHITE);
    myOled->fillRect(0, 0, 128, 12, SSD1306_WHITE);
    myOled->setTextColor(SSD1306_BLACK);
    myOled->printIt(14, 2, "CONFIGURATION WIFI", false, 0);
    myOled->setTextColor(SSD1306_WHITE);
    
    myOled->printIt(2, 17, "Se connecter au WiFi:", true, 0);
    myOled->drawRect(5, 27, 118, 30, SSD1306_WHITE);
    myOled->printIt(15, 30, "SSID: ", false, 0);
    myOled->printIt(55, 30, config.ssid, false, 0);
    myOled->drawLine(10, 40, 118, 40, SSD1306_WHITE);
    myOled->printIt(15, 45, "PASS: ", false, 0);
    myOled->printIt(55, 45, config.password, true, 0);

    wifiManager.setTimeout(config.wifiTimeout);
    wifiManager.setConfigPortalTimeout(config.wifiPortalTimeout);

    bool connected = wifiManager.autoConnect(config.ssid, config.password);
    if (connected)
    {
        Serial.println("Connecté au WiFi !");
        myOled->clearDisplay();
        myOled->drawRect(0, 0, 128, 12, SSD1306_WHITE);
        myOled->fillRect(0, 0, 128, 12, SSD1306_WHITE);
        myOled->setTextColor(SSD1306_BLACK);
        myOled->printIt(25, 2, "WIFI CONNECTE", false, 0);
        myOled->setTextColor(SSD1306_WHITE);
        for(int i = 0; i < 3; i++) {
            myOled->drawCircle(15, 30, 5 + (i*4), SSD1306_WHITE);
        }
        
        myOled->printIt(40, 25, "Reseau:", false, 0);
        myOled->printIt(40, 35, WiFi.SSID().c_str(), true, 0);
        
        return true;
    }
    else
    {
        Serial.println("Échec de la connexion WiFi");
        myOled->clearDisplay();
        myOled->drawRect(0, 0, 128, 12, SSD1306_WHITE);
        myOled->fillRect(0, 0, 128, 12, SSD1306_WHITE);
        myOled->setTextColor(SSD1306_BLACK);
        myOled->printIt(30, 2, "ERREUR WIFI", false, 0);
        myOled->setTextColor(SSD1306_WHITE);
        myOled->drawLine(10, 25, 25, 40, SSD1306_WHITE);
        myOled->drawLine(25, 25, 10, 40, SSD1306_WHITE);
        myOled->printIt(35, 25, "Echec de", false, 0);
        myOled->printIt(35, 35, "connexion", true, 0);
        return false;
    }
}

bool MyPlanteCare::setupMqtt()
{
    Serial.println("Initialisation de la connexion MQTT...");
    myOled->clearDisplay();
    
    myOled->drawRect(0, 0, 128, 12, SSD1306_WHITE);
    myOled->fillRect(0, 0, 128, 12, SSD1306_WHITE);
    myOled->setTextColor(SSD1306_BLACK);
    myOled->printIt(28, 2, "CONFIG MQTT", false, 0);
    myOled->setTextColor(SSD1306_WHITE);
    
    myOled->printIt(10, 20, "Connexion MQTT...", false, 0);
    
    myOled->printIt(75, 35, "...", true, 0);
    
    myMqtt = new MyMqtt(config.mqttServer, config.mqttPort);
    myMqtt->init();
    
    if (myMqtt->connect()) {
        myOled->clearDisplay();
        
        myOled->drawRect(0, 0, 128, 12, SSD1306_WHITE);
        myOled->fillRect(0, 0, 128, 12, SSD1306_WHITE);
        myOled->setTextColor(SSD1306_BLACK);
        myOled->printIt(25, 2, "MQTT CONNECTE", false, 0);
        myOled->setTextColor(SSD1306_WHITE);
        
        myOled->printIt(10, 25, "Connexion reussie", false, 0);   

        myOled->drawLine(55, 40, 60, 45, SSD1306_WHITE);
        myOled->drawLine(60, 45, 70, 35, SSD1306_WHITE);
        
        myOled->display();
        return true;
    } else {
        myOled->clearDisplay();
        
        myOled->drawRect(0, 0, 128, 12, SSD1306_WHITE);
        myOled->fillRect(0, 0, 128, 12, SSD1306_WHITE);
        myOled->setTextColor(SSD1306_BLACK);
        myOled->printIt(25, 2, "ERREUR MQTT", false, 0);
        myOled->setTextColor(SSD1306_WHITE);

        myOled->drawLine(55, 35, 65, 45, SSD1306_WHITE);
        myOled->drawLine(65, 35, 55, 45, SSD1306_WHITE);
        
        myOled->printIt(10, 30, "Echec de connexion", true, 0);
        return false;
    }
}

bool MyPlanteCare::setupMofset()
{
    Serial.println("Initialisation du Mofset...");
    myOled->clearDisplay();
    
    myOled->drawRect(0, 0, 128, 12, SSD1306_WHITE);
    myOled->fillRect(0, 0, 128, 12, SSD1306_WHITE);
    myOled->setTextColor(SSD1306_BLACK);
    myOled->printIt(38, 2, "MOFSET", false, 0);
    myOled->setTextColor(SSD1306_WHITE);
    
    myOled->printIt(45, 30, "Initialisation...", true, 0);
    
    myMofset = new MyMofset(config.mofsetPin);
    if (!myMofset->init())
    {
        Serial.println("Erreur lors de la configuration du Mofset.");
        myOled->clearDisplay();
        
        // Amélioration de l'affichage d'erreur
        myOled->drawRect(0, 0, 128, 12, SSD1306_WHITE);
        myOled->fillRect(0, 0, 128, 12, SSD1306_WHITE);
        myOled->setTextColor(SSD1306_BLACK);
        myOled->printIt(20, 2, "ERREUR MOFSET", false, 0);
        myOled->setTextColor(SSD1306_WHITE);
        
        myOled->drawLine(20, 30, 35, 45, SSD1306_WHITE);
        myOled->drawLine(35, 30, 20, 45, SSD1306_WHITE);
        
        myOled->printIt(50, 30, "Echec", false, 0);
        myOled->printIt(42, 40, "initialisation", true, 0);
        
        return false;
    }
    
    // Test du Mofset
    myMofset->on();
    delay(500);
    myMofset->off();
    
    myOled->clearDisplay();

    myOled->drawRect(0, 0, 128, 12, SSD1306_WHITE);
    myOled->fillRect(0, 0, 128, 12, SSD1306_WHITE);
    myOled->setTextColor(SSD1306_BLACK);
    myOled->printIt(20, 2, "MOFSET PRET", false, 0);
    myOled->setTextColor(SSD1306_WHITE);
    
    myOled->drawCircle(20, 30, 10, SSD1306_WHITE);
    myOled->drawLine(15, 30, 20, 35, SSD1306_WHITE);
    myOled->drawLine(20, 35, 25, 25, SSD1306_WHITE);
    
    myOled->printIt(40, 30, "Initialise", true, 0);
    
    delay(config.setupDelay);
    return true;
}

bool MyPlanteCare::setupMoistureSensor()
{
    Serial.println("Initialisation du capteur d'humidité...");
    myOled->clearDisplay();
    
    myOled->drawRect(0, 0, 128, 12, SSD1306_WHITE);
    myOled->fillRect(0, 0, 128, 12, SSD1306_WHITE);
    myOled->setTextColor(SSD1306_BLACK);
    myOled->printIt(10, 2, "CAPTEUR HUMIDITE", false, 0);
    myOled->setTextColor(SSD1306_WHITE);
    myOled->printIt(40, 30, "Initialisation...", true, 0);
    
    myMoistureSensor = new MyMoistureSensor(config.moistureSensorPin, config.moistureWetValue, config.moistureDryValue);
    if (!myMoistureSensor->init())
    {
        Serial.println("Erreur lors de la configuration du capteur d'humidité.");
        myOled->clearDisplay();
        
        myOled->drawRect(0, 0, 128, 12, SSD1306_WHITE);
        myOled->fillRect(0, 0, 128, 12, SSD1306_WHITE);
        myOled->setTextColor(SSD1306_BLACK);
        myOled->printIt(10, 2, "ERREUR HUMIDITE", false, 0);
        myOled->setTextColor(SSD1306_WHITE);
        
        myOled->drawLine(20, 25, 35, 40, SSD1306_WHITE);
        myOled->drawLine(35, 25, 20, 40, SSD1306_WHITE);
        
        myOled->printIt(50, 30, "Echec", false, 0);
        myOled->printIt(42, 40, "initialisation", true, 0);
        
        return false;
    }
    
    initialMoistureValue = myMoistureSensor->getMoisturePercent();
    
    myOled->clearDisplay();
    
    myOled->drawRect(0, 0, 128, 12, SSD1306_WHITE);
    myOled->fillRect(0, 0, 128, 12, SSD1306_WHITE);
    myOled->setTextColor(SSD1306_BLACK);
    myOled->printIt(5, 2, "CAPTEUR HUMIDITE OK", false, 0);
    myOled->setTextColor(SSD1306_WHITE);
    
    myOled->printIt(20, 25, "Valeur initiale:", false, 0);

    char valueStr[10];
    sprintf(valueStr, "%d%%", initialMoistureValue);
    myOled->setTextSize(2);
    myOled->printIt(48, 35, valueStr, false, 0);
    myOled->setTextSize(1);
    
    myOled->display();
    delay(config.setupDelay);
    return true;
}

bool MyPlanteCare::setupWaterSensor()
{
    Serial.println("Initialisation du capteur d'eau...");
    myOled->clearDisplay();
    
    myOled->drawRect(0, 0, 128, 12, SSD1306_WHITE);
    myOled->fillRect(0, 0, 128, 12, SSD1306_WHITE);
    myOled->setTextColor(SSD1306_BLACK);
    myOled->printIt(15, 2, "CAPTEUR D'EAU", false, 0);
    myOled->setTextColor(SSD1306_WHITE);
    
    myOled->printIt(40, 30, "Initialisation...", true, 0);
    
    myWaterSensor = new MyWaterSensor(config.waterSensorPin, config.waterMaxValue, config.waterMinValue);
    if (!myWaterSensor->init())
    {
        Serial.println("Erreur lors de la configuration du capteur d'eau.");
        myOled->clearDisplay();
        
        myOled->drawRect(0, 0, 128, 12, SSD1306_WHITE);
        myOled->fillRect(0, 0, 128, 12, SSD1306_WHITE);
        myOled->setTextColor(SSD1306_BLACK);
        myOled->printIt(15, 2, "ERREUR CAPTEUR", false, 0);
        myOled->setTextColor(SSD1306_WHITE);
        
        myOled->drawLine(20, 25, 35, 40, SSD1306_WHITE);
        myOled->drawLine(35, 25, 20, 40, SSD1306_WHITE);
        
        myOled->printIt(50, 30, "Echec", false, 0);
        myOled->printIt(42, 40, "initialisation", true, 0);
        
        return false;
    }
    
    initialWaterValue = myWaterSensor->getWaterPercent();
    
    myOled->clearDisplay();
    
    myOled->drawRect(0, 0, 128, 12, SSD1306_WHITE);
    myOled->fillRect(0, 0, 128, 12, SSD1306_WHITE);
    myOled->setTextColor(SSD1306_BLACK);
    myOled->printIt(15, 2, "CAPTEUR EAU OK", false, 0);
    myOled->setTextColor(SSD1306_WHITE);
    
    myOled->printIt(20, 25, "Valeur initiale:", false, 0);

    char valueStr[10];
    sprintf(valueStr, "%d%%", initialWaterValue);
    myOled->setTextSize(2);
    myOled->printIt(48, 35, valueStr, false, 0);
    myOled->setTextSize(1);
    
    myOled->display();
    delay(config.setupDelay);
    return true;
}

void MyPlanteCare::getValues()
{
    int moistureValue = myMoistureSensor->getMoisturePercent();
    int waterValue = myWaterSensor->getWaterPercent();

    myOled->clearDisplay();
    myOled->drawRect(0, 0, 128, 12, SSD1306_WHITE);
    myOled->fillRect(0, 0, 128, 12, SSD1306_WHITE);
    myOled->setTextColor(SSD1306_BLACK);
    myOled->printIt(10, 2, "VALEURS CAPTEURS", false, 0);
    myOled->setTextColor(SSD1306_WHITE);
    
    myOled->printIt(5, 17, "Humidite:", false, 0);
    char moistureStr[10];
    sprintf(moistureStr, "%d%%", moistureValue);
    myOled->printIt(80, 17, moistureStr, false, 0);
    
    myOled->drawLine(5, 27, 123, 27, SSD1306_WHITE);

    myOled->printIt(5, 35, "Niveau eau:", false, 0);
    char waterStr[10];
    sprintf(waterStr, "%d%%", waterValue);
    myOled->printIt(80, 35, waterStr, false, 0);

    statusDoc["moisture"] = moistureValue;
    statusDoc["water"] = waterValue;

    serializeJson(statusDoc, jsonBuffer);

    myMqtt->publish("plantecare/values", jsonBuffer);

    myOled->display();

    delay(config.loopDelay);
}

void MyPlanteCare::startMosfet()
{
    if (moistureValue < 20)
    {
        myMofset->on();
        delay(config.mosfetDelay);
        myMofset->off();
    }
    else if (moistureValue >= 80)
    {
        myMofset->off();
    }
    else
    {
        myMofset->off();
    }
}

