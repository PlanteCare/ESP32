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
    myMqtt = nullptr;
    myOled = nullptr;
    myMofset = nullptr;
    myMoistureSensor = nullptr;
    myWaterSensor = nullptr;
    redLed = nullptr;
    greenLed = nullptr;
    witheLed = nullptr;

    if (_config != nullptr)
    {
        this->config = *_config;
    }
}

MyPlanteCare::~MyPlanteCare()
{
    if (myMqtt != nullptr)
        delete myMqtt;
    if (myOled != nullptr)
        delete myOled;
    if (myMofset != nullptr)
        delete myMofset;
    if (myMoistureSensor != nullptr)
        delete myMoistureSensor;
    if (myWaterSensor != nullptr)
        delete myWaterSensor;
    if (redLed != nullptr)
        delete redLed;
    if (greenLed != nullptr)
        delete greenLed;
    if (witheLed != nullptr)
        delete witheLed;
}

bool MyPlanteCare::init()
{
    if (!setupLeds())
    {
        Serial.println("Erreur lors de la configuration des LEDs.");
        return false;
    }

    if (witheLed != nullptr)
        witheLed->on();

    if (!setupOled())
    {
        Serial.println("Erreur lors de la configuration de l'OLED.");
        if (redLed != nullptr)
            redLed->on();
        return false;
    }

    if (greenLed != nullptr)
        greenLed->blink();

    bool wifiConnected = setupWifi();
    if (!wifiConnected)
    {
        Serial.println("Erreur lors de la configuration du WiFi.");
        if (redLed != nullptr)
            redLed->on();
    }

    if (greenLed != nullptr)
        greenLed->blink();

    bool mqttConnected = false;
    if (wifiConnected)
    {
        mqttConnected = setupMqtt();
        if (!mqttConnected)
        {
            Serial.println("Erreur lors de la configuration du MQTT.");
        }
    }

    if (greenLed != nullptr)
        greenLed->blink();

    if (!setupMofset())
    {
        Serial.println("Erreur lors de la configuration du Mofset.");
        if (redLed != nullptr)
            redLed->on();
        return false;
    }

    if (greenLed != nullptr)
        greenLed->blink();

    if (!setupMoistureSensor())
    {
        Serial.println("Erreur lors de la configuration du capteur d'humidité.");
        if (redLed != nullptr)
            redLed->on();
        return false;
    }

    if (greenLed != nullptr)
        greenLed->blink();

    if (!setupWaterSensor())
    {
        Serial.println("Erreur lors de la configuration du capteur d'eau.");
        if (redLed != nullptr)
            redLed->on();
        return false;
    }

    if (greenLed != nullptr)
        greenLed->blink();

    statusDoc["esp"] = "1";
    statusDoc["moisture"] = "1";
    statusDoc["water"] = "1";

    if (witheLed != nullptr)
        witheLed->off();
    if (greenLed != nullptr)
        greenLed->on();

    return true;
}

bool MyPlanteCare::setupLeds()
{
    redLed = new MyLed(config.redLedPin, config.ledsBlinkDelay);
    if (!redLed->init())
    {
        Serial.println("Erreur lors de la configuration de la LED rouge.");
        delete redLed;
        redLed = nullptr;
        return false;
    }

    greenLed = new MyLed(config.greenLedPin, config.ledsBlinkDelay);
    if (!greenLed->init())
    {
        Serial.println("Erreur lors de la configuration de la LED verte.");
        delete redLed;
        redLed = nullptr;
        delete greenLed;
        greenLed = nullptr;
        return false;
    }

    witheLed = new MyLed(config.witheLedPin, config.ledsBlinkDelay);
    if (!witheLed->init())
    {
        Serial.println("Erreur lors de la configuration de la LED blanche.");
        delete redLed;
        redLed = nullptr;
        delete greenLed;
        greenLed = nullptr;
        delete witheLed;
        witheLed = nullptr;
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
    if (myOled->init(config.oledSplashDelay) != 0)
    {
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
        for (int i = 0; i < 3; i++)
        {
            myOled->drawCircle(15, 30, 5 + (i * 4), SSD1306_WHITE);
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

    if (myMqtt->connect())
    {
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
    }
    else
    {
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
    if (myMoistureSensor == nullptr || myWaterSensor == nullptr || myOled == nullptr || myMofset == nullptr)
    {
        Serial.println("Erreur: Capteurs non initialisés");
        return;
    }

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

    if (moistureValue < 20 && waterValue > 10)
    {
        myOled->printIt(5, 50, "Arrosage en cours...", false, 0);
        myMofset->on();
        delay(config.mosfetDelay);
        myMofset->off();
    }
    else if (moistureValue < 20 && waterValue <= 10)
    {
        myOled->printIt(5, 50, "Niveau eau trop bas!", false, 0);
    }
    else
    {
        myOled->printIt(5, 50, "Humidite adequate", false, 0);
    }
    if (myMqtt != nullptr)
    {
        String macAddress = WiFi.macAddress();

        StaticJsonDocument<200> valuesDoc;
        JsonObject esp_values = valuesDoc.createNestedObject(macAddress);

        esp_values["moisture"] = moistureValue;
        esp_values["water"] = waterValue;

        String jsonString;
        serializeJson(valuesDoc, jsonString);

        myMqtt->publish(config.mqttValuesTopic, jsonString.c_str());
    }

    myOled->display();

    delay(config.loopDelay);
}

void MyPlanteCare::checkHealthStatus()
{
    String macAddress = WiFi.macAddress();

    StaticJsonDocument<200> statusDoc;
    JsonObject esp_status = statusDoc.createNestedObject(macAddress);

    bool moistureSensorOk = (myMoistureSensor != nullptr && myMoistureSensor->isWorking());
    bool waterSensorOk = (myWaterSensor != nullptr && myWaterSensor->isWorking());

    esp_status["moisture_sensor"] = moistureSensorOk ? 1 : 0;
    esp_status["water_sensor"] = waterSensorOk ? 1 : 0;
    esp_status["esp"] = (moistureSensorOk && waterSensorOk) ? 1 : 0;

    String jsonString;
    serializeJson(statusDoc, jsonString);

    myMqtt->publish(config.mqttStatusTopic, jsonString.c_str());
}
