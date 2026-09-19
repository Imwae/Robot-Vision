/*

wirelessManager searches for the network signal based on configured NET_SSID and NET_PASS in secrets.h

Establish initial connection, and checks connection after initial establishment

All credentials and sensitive information are purposefully hidden in secrets.h
Examples on calls to secrets.h are publicly available in secrets_example.h

*/

#include <WiFi.h>
#include <Arduino.h>
#include "wirelessManager.h"
#include "secrets.h"

const int attempts = 10;

// Initial connection that return true if connected, otherwise false if couldnt connect in the specified attempt limit
bool connectNetwork() {

    WiFi.begin(NET_SSID, NET_PASS);

    for (int i = 0; i < attempts; i++) {
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

// Checks connections to see whether connection is still stable (true) or dropped (false)
bool checkConnection() {

    static bool lastStateConnected = true;

    if (WiFi.status() != WL_CONNECTED) {
        if (lastStateConnected) {
            Serial.println("Connection lost, retrying... ");
        }

        lastStateConnected = false;

    } else {
        if (!lastStateConnected) {
            Serial.println("Connection reconnected!"); 
        }

        lastStateConnected = true;
    }

    return lastStateConnected;
}

// Finds all possible SSIDs nearby and prints out in a list order

void printSsid() {
    int count = WiFi.scanNetworks();

    for (int i = 0; i < count; i++) {
        Serial.println(WiFi.SSID(i));
    }
}