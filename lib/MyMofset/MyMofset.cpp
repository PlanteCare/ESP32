/**
 * @file MyMofset.cpp
 * @author Lyes Hamrani
 * @brief Implementation de la classe MyMofset
 * @version 1.0
 * @date Création : 28/03/2025
 * @date Dernière mise à jour : 28/03/2025
 */
#include "MyMofset.h"

/**
 * @brief Constructeur de la classe MyMofset
 * 
 * @date Création 28/03/2025
 * @brief Constructeur de la classe MyMofset
 * 
 * @param _mofsetPin Pin du Mofset
 */
MyMofset::MyMofset(int _mofsetPin) {
    mofsetPin = _mofsetPin;
}

/// @brief Destructeur de la classe MyMofset
MyMofset::~MyMofset() {}

/**
 * Initialise le Mofset
 *
 * @date Création 28/03/2025
 * @brief Initialisation du Mofset
 *
 * @return true si l'initialisation est réussie
 */
bool MyMofset::init() {
    pinMode(mofsetPin, OUTPUT);
    off(); 
    return true;
}

/**
 * Allume le Mofset
 *
 * @date Création 28/03/2025
 * @brief Allumage du Mofset
 */
void MyMofset::on() {
    digitalWrite(mofsetPin, HIGH);
}

/**
 * Eteint le Mofset
 *
 * @date Création 28/03/2025
 * @brief Extinction du Mofset
 */
void MyMofset::off() {
    digitalWrite(mofsetPin, LOW);
}