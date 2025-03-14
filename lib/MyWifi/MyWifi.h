/**
 * Classe MyWifi
 * Gestion du wifi sur l'esp32
 * @file MyWifi.h
 * @author Lyes Hamrani
 * @brief Declaration de la classe MyWifi
 * @version 1.1
 * @date Création : 05/09/2024
 * @date Dernière mise à jour : 10/10/2024
 */
#ifndef MyWifi_h
#define MyWifi_h
#include <WiFi.h>

class MyWifi
{
public:
    MyWifi();
    ~MyWifi();
    bool init(const char *_ssid, const char *_password);
    void connect();
    void disconnect();
    bool isConnected();
    String getMac();

private:
    IPAddress getIP();
    const char *ssid; 
    const char *password; 
    bool connected; 
};

#endif