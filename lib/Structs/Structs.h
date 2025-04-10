#ifndef STRUCTS_H
#define STRUCTS_H

struct planteCareConfig {
    /*-----------LEDS-----------*/
    int redLedPin;
    int greenLedPin;
    int witheLedPin;
    int ledsBlinkDelay;
    /*-----------SENSORS-----------*/
    int mofsetPin;
    int moistureSensorPin;
    int moistureDryValue;
    int moistureWetValue;
    int waterSensorPin;
    int waterMaxValue;
    int waterMinValue;
    /*-----------WIFI-----------*/
    const char* ssid;
    const char* password;
    int wifiTimeout;
    int wifiPortalTimeout;
    /*-----------MQTT-----------*/
    const char* mqttServer;
    int mqttPort;
    const char* mqttTopic;
    /*-----------OLED-----------*/
    int oledWidth;
    int oledHeight;
    int oledResPin;
    int oledSplashDelay;

    /*-----------OTHER-----------*/
    int setupDelay;
};

#endif