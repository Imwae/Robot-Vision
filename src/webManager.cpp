#include <ESPAsyncWebServer.h>
#include <Arduino.h>
#include "webManager.h"

static AsyncWebServer server(80);
static AsyncWebSocket ws("/ws");

static char storedCharacter = '\0';
static unsigned long lastMessageTime = 0;


void setupWebPage() {

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html", "<h1>hello</h1>");
    });

    ws.onEvent([](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {

        if (type == WS_EVT_DATA) {
        Serial.printf("%s\n", (char *)data);
        storedCharacter = (char) *data;
        lastMessageTime = millis();

        }
    
    }); 

    server.addHandler(&ws);

    server.begin();

}

char getInputCharacter() {

    if (millis() - lastMessageTime >  200) {
        storedCharacter = '\0';
    }

    return storedCharacter;

}
