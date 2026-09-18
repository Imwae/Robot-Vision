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
            return true;
        }

        Serial.println("Connecting... ");
    }

    return false;
}