/**
 * Classe MyMqtt
 * Gestion du mqtt sur l'esp32
 * @file MyMqtt.h
 * @author Lyes Hamrani
 * @brief Declaration de la classe MyMqtt
 * @version 1.1
 * @date Création : 05/09/2024
 * @date Dernière mise à jour : 10/10/2024
 */
#ifndef MyMqtt_h
#define MyMqtt_h

#include <PubSubClient.h>
#include <WiFiClient.h>
#include <WiFi.h>

class MyMqtt {
public:
    MyMqtt();
    ~MyMqtt();
    bool init(const char* _mqttServer, int _mqttPort);
    bool connect();
    void disconnect();
    bool isConnected();
    bool publish(const char* topic ,const char* message);
    bool subscribe(const char* topic);
    void loop();

private:
    PubSubClient client;
    WiFiClient espClient;
    String idClient;
    const char* mqttServer;
    int mqttPort;
    bool connected;
    static void callback(char* topic, byte* payload, unsigned int length);
};

#endif