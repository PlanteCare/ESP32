/**
 * Classe MyMoistureSensor
 * Gestion du capteur d'humidité du sol
 * @file MyMoistureSensor.h
 * @author Lyes Hamrani
 * @brief Declaration de la classe MyMoistureSensor
 * @version 1.0
 * @date Création : 20/03/2025
 * @date Dernière mise à jour : 20/03/2025
 */
#ifndef MyMoistureSensor_h
#define MyMoistureSensor_h
#include <Arduino.h>

class MyMoistureSensor
{
public:
    MyMoistureSensor();
    ~MyMoistureSensor();
    bool init(int _pin, int _dryValue, int _wetValue);
    String getMoisture();

private:
    int pin;
    int dryValue;
    int wetValue;
    int moistureValue;
    int moisturePercent; // Correction de 'moiusturePercent' en 'moisturePercent'
    int getMoisturePercent();
};

#endif