/**
 * Gestion du capteur d'humidité du sol
 *
 * @file MyWaterSensor.cpp
 * @author Lyes Hamrani
 * @brief Methode de la classe MyWaterSensor
 * @version 1.0
 * @date Création : 20/03/2025
 * @date Dernière mise à jour : 20/03/2025
 */
#include "MyWaterSensor.h"

/// @brief Constructeur de la classe MyWaterSensor
MyWaterSensor::MyWaterSensor() {}

/// @brief Destructeur de la classe MyWaterSensor
MyWaterSensor::~MyWaterSensor() {}

/**
 * Initialise les paramètres du capteur d'humidité
 * 
 * @date Création 20/03/2025
 * @brief Initialisation du capteur d'humidité
 * 
 * @param _waterSensorPin Pin de lecture du capteur
 * @param _waterMaxValue Valeur de référence pour le niveau d'eau maximum
 * @param _waterMinValue Valeur de référence pour le niveau d'eau minimum
 */
bool MyWaterSensor::init(int _waterSensorPin, int _waterMaxValue, int _waterMinValue) {
    waterSensorPin = _waterSensorPin;
    waterMaxValue = _waterMaxValue;
    waterMinValue = _waterMinValue;
    pinMode(waterSensorPin, INPUT);
    return true;
}

/**
 * Récupère le pourcentage d'eau
 * 
 * @date Création 20/03/2025
 * @brief Récupération du pourcentage d'eau
 * 
 * @return Pourcentage d'eau
 */
int MyWaterSensor::getWaterPercent() {
    waterValue = analogRead(waterSensorPin);
    waterValue = constrain(waterValue, waterMinValue, waterMaxValue);
    return map(waterValue, waterMinValue, waterMaxValue, 0, 100);
}