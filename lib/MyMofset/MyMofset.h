/**
 * @file MyMofset.h
 * @author Lyes Hamrani
 * @brief Declaration de la classe MyMofset
 * @version 1.0
 * @date Création : 28/03/2025
 * @date Dernière mise à jour : 28/03/2025
 */
#ifndef MYMOFSET_H
#define MYMOFSET_H
#include <Arduino.h>

class MyMofset
{
private:
    int mofsetPin;
public:
    MyMofset();
    ~MyMofset();
    bool init(int _mofsetPin);
    void on();
    void off();
};

#endif