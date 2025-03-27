/**
 * Gestion du capteur d'humidité du sol
 *
 * @file MyMoistureSensor.cpp
 * @author Lyes Hamrani
 * @brief Methode de la classe MyMoistureSensor
 * @version 1.0
 * @date Création : 20/03/2025
 * @date Dernière mise à jour : 20/03/2025
 */
#include "MyMoistureSensor.h"

/// @brief Constructeur de la classe MyMoistureSensor
MyMoistureSensor::MyMoistureSensor() {}

/// @brief Destructeur de la classe MyMoistureSensor
MyMoistureSensor::~MyMoistureSensor() {}

/**
 * Initialise les paramètres du capteur d'humidité
 *
 * @date Création 20/03/2025
 * @brief Initialisation du capteur d'humidité
 *
 * @param _pin Pin de lecture du capteur
 * @param _dryValue Valeur de référence pour le sol sec
 * @param _wetValue Valeur de référence pour le sol humide
 */
bool MyMoistureSensor::init(int _pin, int _dryValue, int _wetValue) {
    pin = _pin;
    dryValue = _dryValue;
    wetValue = _wetValue;
    pinMode(pin, INPUT);
    return true;
}

/**
 * Récupère le pourcentage d'humidité du sol
 *
 * @date Création 20/03/2025
 * @brief Récupération du pourcentage d'humidité
 *
 * @return Pourcentage d'humidité
 */
int MyMoistureSensor::getMoisturePercent() {
    moistureValue = analogRead(pin);
    moistureValue = constrain(moistureValue, wetValue, dryValue);
    return map(moistureValue, dryValue, wetValue, 0, 100);
}