# Documentation Projet ESP32

## Aperçu

Ce projet est un firmware pour microcontrôleurs ESP32 destiné au suivi de pots de plantes. Il se connecte aux réseaux WiFi et MQTT pour envoyer des données des plantes à un serveur central dans le cadre du système PlanteCare.

## Structure du Projet

```
ESP32/
├── lib/                        # Bibliothèques spécifiques au projet
│   ├── MyMqtt/                 # Bibliothèque de gestion MQTT
│   │   ├── MyMqtt.h           # Déclaration de la classe MQTT
│   │   └── MyMqtt.cpp         # Implémentation de la classe MQTT
├── platformio.ini              # Configuration PlatformIO
└── src/                        # Code source principal
    └── main.cpp                # Point d'entrée du programme
```

## Composants Principaux

### 1. WiFiManager

Le projet utilise la bibliothèque WiFiManager pour gérer la connexion WiFi de l'ESP32 de manière conviviale.

**Fonctionnalités :**
- Configuration WiFi via un portail captif sans coder les identifiants
- Stockage automatique des paramètres de connexion en mémoire
- Création d'un point d'accès temporaire lorsqu'aucune connexion n'est disponible
- Prise en charge de la reconnexion automatique
- Configuration possible via interface web (192.168.4.1)

**Utilisation :**
```cpp
#include <WiFiManager.h>

WiFiManager wifiManager;
wifiManager.autoConnect("PlanteCare-AP", "password");
```

### 2. Classe MyMqtt (lib/MyMqtt/)

La classe `MyMqtt` gère la connexion et la communication MQTT.

**Fonctionnalités :**
- Initialisation et connexion au serveur MQTT
- Publication de messages sur des topics
- Abonnement à des topics
- Gestion des messages reçus via callback

### 3. Programme Principal (src/main.cpp)

Le fichier `main.cpp` contient le code principal qui configure WiFiManager et utilise la classe MyMqtt.

**Configuration :**
- `MQTT_SERVER` : "api.lyeshamrani.com"
- `MQTT_PORT` : 8883
- `MQTT_TOPIC` : "plantecare/message"
- `LOOP_DELAY` : 60000 ms (1 minute)
- `AP_NAME` : "PlanteCare-AP" (nom du point d'accès WiFi)
- `AP_PASSWORD` : "password" (mot de passe du point d'accès)

**Fonctionnement :**
1. Initialisation de la communication série
2. Configuration et connexion au WiFi via WiFiManager
3. Connexion au serveur MQTT
4. Envoi périodique du message "Hello from ESP32" sur le topic MQTT
5. Vérification de l'état de la connexion WiFi à chaque boucle

## Configuration PlatformIO

Le fichier `platformio.ini` contient la configuration suivante :

```ini
[env:esp32doit-devkit-v1]
platform = espressif32
board = esp32doit-devkit-v1
framework = arduino
lib_deps =
    knolleary/PubSubClient@^2.8
    tzapu/WiFiManager@^2.0.17
```

## Auteur

Lyes Hamrani