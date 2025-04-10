/**
 * Classe MyMoistureSensor
 * Gestion du capteur d'humidité du sol
 * @file MyWaterSensor.h
 * @author Lyes Hamrani
 * @brief Declaration de la classe MyWaterSensor
 * @version 1.0
 * @date Création : 20/03/2025
 * @date Dernière mise à jour : 20/03/2025
 */
#ifndef MyWaterSensor_h
#define MyWaterSensor_h
#include <Arduino.h>

class MyWaterSensor
{
    public:
        MyWaterSensor(int _waterSensorPin, int _waterMaxValue, int _waterMinValue);
        ~MyWaterSensor();
        bool init();
        int getWaterPercent();
    private:
        int waterSensorPin;
        int waterMaxValue;
        int waterMinValue;
        int waterValue;
};

#endif