/**
 * Gestion du mqtt sur l'esp32
 *
 * @file MyMqtt.cpp
 * @author Lyes Hamrani
 * @brief Methode de la classe MyMqtt
 * @version 1.1
 * @date Création : 05/09/2024
 * @date Dernière mise à jour : 10/10/2024
 */
#include "MyMqtt.h"

MyMqtt::MyMqtt() {}

MyMqtt::~MyMqtt() {}

/**
 * init initialise de la classe MyMqtt
 * Initialise les paramètres de connexion
 * 
 * @date Création 05/09/2024
 * @brief Initialisation de la connexion
 * 
 * @param _mqttServer Adresse du serveur mqtt
 * @param _mqttPort Port du serveur mqtt
 * 
 * @return true si l'initialisation est réussie
 */
bool MyMqtt::init(const char* _mqttServer, int _mqttPort) {
    mqttServer = _mqttServer;
    mqttPort = _mqttPort;
    client.setClient(espClient);
    client.setServer(mqttServer, mqttPort);
    return true;
}

/**
 * Connecte l'esp32 au serveur mqtt
 * 
 * @date Création 05/09/2024
 * @brief Connexion au serveur mqtt
 * 
 * @return true si la connexion est réussie 
 */
bool MyMqtt::connect() {
    unsigned long start = millis();
    unsigned long timeout = 5000;
    while (!client.connected() && millis() - start < timeout) {
        idClient += String(WiFi.macAddress());
        Serial.printf("Connexion du client %s au serveur MQTT %s:%d\n", idClient.c_str(), mqttServer, mqttPort);
        if (client.connect(idClient.c_str())) {
            Serial.println("Connecté au serveur MQTT");
            client.setCallback(callback);
            connected = true;
            return true;
        } else {
            Serial.print("Echec de la connexion au serveur MQTT, état: ");
            Serial.print(client.state());
            Serial.println(" Nouvelle tentative dans 2 secondes");
            delay(2000);
        }
    }
    return false;
}

/**
 * Déconnecte l'esp32 du serveur mqtt
 * 
 * @date Création 05/09/2024
 * @brief Déconnexion du serveur mqtt
 * 
 */
void MyMqtt::disconnect() {
    client.disconnect();
    connected = false;
}

/**
 * Vérifie si l'esp32 est connecté au serveur mqtt
 * 
 * @date Création 05/09/2024
 * @brief Vérification de la connexion
 * 
 * @return true si l'esp32 est connecté au serveur mqtt et false si non
 */
bool MyMqtt::isConnected() {
    return client.connected();
}

/**
 * Envoie un message sur un topic
 * 
 * @date Création 05/09/2024
 * @brief Envoie d'un message
 * 
 * @param topic Nom du topic
 * @param message Message à envoyer
 * 
 * @return true si l'envoie est réussi
 */
bool MyMqtt::publish(const char* topic ,const char* message) {
    return client.publish(topic, message);
}

/**
 * Souscrit à un topic
 * 
 * @date Création 05/09/2024
 * @brief Souscription à un topic
 * 
 * @param topic Nom du topic
 * 
 * @return true si la souscription est réussie
 */
bool MyMqtt::subscribe(const char* topic) {
    return client.subscribe(topic);
}

/**
 * Boucle de gestion des messages
 * 
 * @date Création 05/09/2024
 * @brief Boucle de gestion des messages
 * 
 */
void MyMqtt::loop() {
    client.loop();
}

/**
 * Callback appelé lors de la réception d'un message
 * 
 * @date Création 05/09/2024
 * @brief Callback de réception de message
 * 
 * @param topic Nom du topic
 * @param payload Message reçu
 * @param length Taille du message
 * 
 * @return void
 */
void MyMqtt::callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message reçu sur le topic [");
    Serial.print(topic);
    Serial.print("]: ");
    for (unsigned int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------------------------------------------------");
}