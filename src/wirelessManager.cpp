#include <WiFi.h>
#include <Arduino.h>
#include "wirelessManager.h"
#include "secrets.h"

const int seconds = 10;

bool connectNetwork() {

    WiFi.begin(NET_SSID, NET_PASS);

    for (int i = 0; i < seconds; i++) {
        delay(1000);

        if (WiFi.status() == WL_CONNECTED) {
            Serial.print("IP Address: ");
            Serial.println(WiFi.localIP());
            WiFi.setAutoReconnect(true); // sets auto reconnect 
            return true;
        }

        Serial.println("Connecting... ");
    }

    return false;
}

bool checkConnection() {

    static bool lastStateConnected = true;

    if (WiFi.status() != WL_CONNECTED) {
        if (lastStateConnected) {
            Serial.println("Connection lost, retrying... ");
        }

        lastStateConnected = false;
        return false;

    } else {
        if (!lastStateConnected) {
            Serial.println("Connection reconnected!"); 
        }

        lastStateConnected = true;
        return true;
    }
}

void printSsid() {
    int count = WiFi.scanNetworks();

    for (int i = 0; i < count; i++) {
        Serial.println(WiFi.SSID(i));
    }
}