#include "MyMofset.h"

/// @brief Constructeur de la classe MyMofset
MyMofset::MyMofset() {}

/// @brief Destructeur de la classe MyMofset
MyMofset::~MyMofset() {}

/**
 * Initialise les paramètres du Mofset
 *
 * @date Création 28/03/2025
 * @brief Initialisation du Mofset
 *
 * @param _mofsetPin Pin de la led
 */
bool MyMofset::init(int _mofsetPin) {
    mofsetPin = _mofsetPin;
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