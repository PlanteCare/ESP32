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
│   └── MyWifi/                 # Bibliothèque de gestion WiFi
│       ├── MyWifi.h           # Déclaration de la classe WiFi
│       └── MyWifi.cpp         # Implémentation de la classe WiFi
├── platformio.ini              # Configuration PlatformIO
└── src/                        # Code source principal
    └── main.cpp                # Point d'entrée du programme
```

## Composants Principaux

### 1. Classe MyWifi (lib/MyWifi/)

La classe `MyWifi` gère la connexion WiFi de l'ESP32.

**Fonctionnalités :**
- Initialisation et connexion au réseau WiFi
- Déconnexion du réseau WiFi
- Vérification de l'état de la connexion
- Récupération de l'adresse IP et MAC

### 2. Classe MyMqtt (lib/MyMqtt/)

La classe `MyMqtt` gère la connexion et la communication MQTT.

**Fonctionnalités :**
- Initialisation et connexion au serveur MQTT
- Publication de messages sur des topics
- Abonnement à des topics
- Gestion des messages reçus via callback

### 3. Programme Principal (src/main.cpp)

Le fichier `main.cpp` contient le code principal qui configure et utilise les classes MyWifi et MyMqtt.

**Configuration :**
- `MQTT_SERVER` : "lyeshamrani.com"
- `MQTT_PORT` : 1883
- `WIFI_SSID` : "GIGACHAD"
- `WIFI_PASSWORD` : "BigNoobs999"
- `MQTT_TOPIC` : "plantecare/message"
- `LOOP_DELAY` : 60000 ms (1 minute)

**Fonctionnement :**
1. Initialisation de la communication série
2. Connexion au WiFi
3. Connexion au serveur MQTT
4. Envoi périodique du message "Hello from ESP32" sur le topic MQTT

## Configuration PlatformIO

Le fichier `platformio.ini` contient la configuration suivante :

```ini
[env:esp32doit-devkit-v1]
platform = espressif32
board = esp32doit-devkit-v1
framework = arduino
lib_deps =
    knolleary/PubSubClient@^2.8
```

## Auteur

Lyes Hamrani
