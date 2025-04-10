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


/**
 * @brief Constructeur de la classe MyLed
 * 
 * @date Création 27/03/2025
 * @brief Constructeur de la classe MyLed
 * 
 * @param _ledPin Pin de la led
 * @param _delay Délai de clignotement
 */
MyLed::MyLed(int _ledPin, int _delay) {
    ledPin = _ledPin;
    blinkDelay = _delay;
}

/// @brief Destructeur de la classe MyLed
MyLed::~MyLed() {}

/**
 * Initialise la led
 * 
 * @date Création 27/03/2025
 * @brief Initialisation de la led
 * 
 * @return true si l'initialisation est réussie
 */
bool MyLed::init() {
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
    digitalWrite(ledPin, HIGH);
}

/**
 * Eteint la led
 * 
 * @date Création 27/03/2025
 * @brief Extinction de la led
 */
void MyLed::off() {
    digitalWrite(ledPin, LOW);
}

/**
 * Fait clignoter la led
 * 
 * @date Création 27/03/2025
 * @brief Clignotement de la led
 */
void MyLed::blink() {
    on();
    delay(blinkDelay);
    off();
}