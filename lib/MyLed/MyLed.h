/**
 * Classe de gestion de l'allumage d'une led
 *
 * @file MyLed.h
 * @author Lyes Hamrani
 * @brief Declaration de la classe MyLed
 * @version 1.0
 * @date Création : 27/03/2025
 * @date Dernière mise à jour : 27/03/2025
 */
#ifndef MYLED_H
#define MYLED_H
#include <Arduino.h>

class MyLed
{
public:
    MyLed();
    ~MyLed();
    bool init(int _ledPin);
    void on();
    void off();
    void blink(int _delay);

    private:
    int ledPin;
    int blinkDelay;
};

#endif