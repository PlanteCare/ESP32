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

/**
 * @brief Constructeur de la classe MyWaterSensor
 * 
 * @date Création 20/03/2025
 * @brief Constructeur de la classe MyWaterSensor
 * 
 * @param _waterSensorPin Pin du capteur d'humidité
 * @param _waterMaxValue Valeur maximale de l'humidité
 * @param _waterMinValue Valeur minimale de l'humidité
 */
MyWaterSensor::MyWaterSensor(int _waterSensorPin, int _waterMaxValue, int _waterMinValue) {
    waterSensorPin = _waterSensorPin;
    waterMaxValue = _waterMaxValue;
    waterMinValue = _waterMinValue;
}

/// @brief Destructeur de la classe MyWaterSensor
MyWaterSensor::~MyWaterSensor() {}

/**
 * Initialise du capteur d'humidité
 * 
 * @date Création 20/03/2025
 * @brief Initialisation du capteur d'humidité
 * 
 * @return true si l'initialisation est réussie
 */
bool MyWaterSensor::init() {
    pinMode(waterSensorPin, INPUT);
    if (analogRead(waterSensorPin) < 0 || analogRead(waterSensorPin) >= 4095) {
        return false;
    }
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