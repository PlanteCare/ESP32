/**
 * Gestion du wifi sur l'esp32
 *
 * @file MyWifi.cpp
 * @author Lyes Hamrani
 * @brief Methode de la classe MyWifi
 * @version 1.1
 * @date Création : 05/09/2024
 * @date Dernière mise à jour : 10/10/2024
 */
#include "MyWifi.h"

MyWifi::MyWifi() {}

MyWifi::~MyWifi() {}

/**
 * init initialise de la classe MyWifi
 * Initialise les paramètres de connexion
 * 
 * @date Création 05/09/2024
 * @brief Initialisation de la connexion
 * 
 * @param _ssid Nom du réseau
 * @param _password Mot de passe du réseau
 * @return true si l'initialisation est réussie
 */
bool MyWifi::init(const char *_ssid, const char *_password)
{
    ssid = _ssid;
    password = _password;
    connected = false;
    return true;
}

/**
 * Connecte l'esp32 au réseau wifi
 * 
 * @date Création 05/09/2024
 * @brief Connexion au réseau wifi
 */
void MyWifi::connect() {
    delay(100);
    Serial.print("\nConnexion au réseau: ");
    Serial.println(ssid);
    Serial.println(password);
    WiFi.begin(ssid, password);
    
    unsigned long start = millis();
    unsigned long timeout = 10000;
    
    while (WiFi.status() != WL_CONNECTED && millis() - start < timeout) {
        delay(500);
        Serial.print(".");
    }
    
    // Vérifier si la connexion est réellement établie
    if (WiFi.status() == WL_CONNECTED) {
        Serial.print("\nConnecté");
        Serial.print("\nAdresse IP: ");
        Serial.println(getIP());
        connected = true;
    } else {
        Serial.println("\nÉchec de la connexion - délai dépassé");
        connected = false;
    }
}

/**
 * Déconnecte l'esp32 du réseau wifi
 * 
 * @date Création 05/09/2024
 * @brief Déconnexion du réseau wifi
 */
void MyWifi::disconnect()
{
    WiFi.disconnect();
}

/**
 * Vérifie si l'esp32 est connecté au réseau wifi
 * 
 * @date Création 05/09/2024
 * @brief Vérification de la connexion
 * @return true si l'esp32 est connecté au WIFI et false si non
 */
bool MyWifi::isConnected()
{
    connected = (WiFi.status() == WL_CONNECTED ? true : false);
    return connected;
}

/**
 * Retourne l'adresse IP de l'esp32
 * 
 * @date Création 05/09/2024
 * @brief Adresse IP de l'esp32
 * @return Adresse IP de l'esp32
 */
IPAddress MyWifi::getIP()
{
    return WiFi.localIP();
}

/**
 * Retourne l'adresse MAC de l'esp32
 * 
 * @date Création 05/09/2024
 * @brief Adresse MAC de l'esp32
 * @return Adresse MAC de l'esp32
 */
String MyWifi::getMac()
{
    return WiFi.macAddress();
}