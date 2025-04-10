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

/**
 * @brief Constructeur de la classe MyMoistureSensor
 *
 * @date Création 20/03/2025
 * @brief Constructeur de la classe MyMoistureSensor
 *
 * @param _pin Pin du capteur d'humidité
 * @param _dryValue Valeur de l'humidité sèche
 * @param _wetValue Valeur de l'humidité humide
 */
MyMoistureSensor::MyMoistureSensor(int _pin, int _dryValue, int _wetValue) {
    pin = _pin;
    dryValue = _dryValue;
    wetValue = _wetValue;
}

/// @brief Destructeur de la classe MyMoistureSensor
MyMoistureSensor::~MyMoistureSensor() {}

/**
 * Initialise le capteur d'humidité
 *
 * @date Création 20/03/2025
 * @brief Initialisation du capteur d'humidité
 *
 * @return true si l'initialisation est réussie
 */
bool MyMoistureSensor::init() {
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