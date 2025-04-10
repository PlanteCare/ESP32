#ifndef MY_PLANT_CARE_H
#define MY_PLANT_CARE_H
/**
 * Classe controleur pour un pot de fleurs intelligent (PlanteCare)
 * @file MyPlanteCare.h
 * @name MyPlanteCare
 * @brief Declaration de la classe controleur MyPlanteCare
 *
 * @authors Lyes Hamrani
 * @version 1.0
 * @date Création : 28/03/2025
 * @date Dernière mise à jour : 28/03/2025
 */

/*-----------INCLUSIONS-----------*/
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include "MyMqtt.h"
#include "MyMoistureSensor.h"
#include "MyWaterSensor.h"
#include "MyOled.h"
#include "MyLed.h"
#include "MyMofset.h"
#include "Structs.h"


class MyPlanteCare
{
private:
    /*-----------OBJETS-----------*/
    WiFiManager wifiManager;
    MyMqtt *myMqtt = nullptr;
    MyOled *myOled = nullptr;
    MyMofset *myMofset = nullptr;
    MyMoistureSensor *myMoistureSensor = nullptr;
    MyWaterSensor *myWaterSensor = nullptr;
    MyLed *redLed = nullptr;
    MyLed *greenLed = nullptr;
    MyLed *witheLed = nullptr;

    /*-----------CONFIGURATION-----------*/
    planteCareConfig config;

    /*-----------METHODES-----------*/
    bool setupLeds();
    bool setupOled();
    bool setupWifi();
    bool setupMqtt();
    bool setupMofset();
    bool setupMoistureSensor();
    bool setupWaterSensor();

public:
    MyPlanteCare(planteCareConfig *_config);
    ~MyPlanteCare();
    bool init();
};

#endif
