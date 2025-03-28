/**
 * Gestion de l'allumage d'une led 
 *
 * @file MyLed.cpp
 * @author Lyes Hamrani
 * @brief Methode de la classe MyLed
 * @version 1.0
 * @date Création : 27/03/2025
 * @date Dernière mise à jour : 27/03/2025
 */
#include "MyLed.h"


/// @brief Constructeur de la classe MyLed
MyLed::MyLed() {}

/// @brief Destructeur de la classe MyLed
MyLed::~MyLed() {}

/**
 * Initialise les paramètres de la led
 * 
 * @date Création 27/03/2025
 * @brief Initialisation de la led
 * 
 * @param _ledPin Pin de la led
 */
bool MyLed::init(int _ledPin) {
    ledPin = _ledPin;
    pinMode(ledPin, OUTPUT);
    off();
    return true;
}

/**
 * Allume la led
 * 
 * @date Création 27/03/2025
 * @brief Allumage de la led
 */
void MyLed::on() {
    digitalWrite(ledPin, LOW);
}

/**
 * Eteint la led
 * 
 * @date Création 27/03/2025
 * @brief Extinction de la led
 */
void MyLed::off() {
    digitalWrite(ledPin, HIGH);
}

/**
 * Fait clignoter la led
 * 
 * @date Création 27/03/2025
 * @brief Clignotement de la led
 * 
 * @param _delay Délai de clignotement
 */
void MyLed::blink(int _delay) {
    blinkDelay= _delay;
    digitalWrite(ledPin, LOW);
    delay(blinkDelay);
    digitalWrite(ledPin, HIGH);
    delay(blinkDelay);
}