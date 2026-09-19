/* 

webManager runs the HTTP and WebSocket servers, where HTTP serves the control page on request, while WebSocket actively
detects live commands.  In this case, it is detecting specific key presses, such as W A S D. 


Timeout occurs when keypresses have been stale for more than 200 ms. 

*/


#include <ESPAsyncWebServer.h>
#include <Arduino.h>
#include "webManager.h"

static AsyncWebServer server(80);
static AsyncWebSocket ws("/ws");

static char storedCharacter = '\0';
static unsigned long lastMessageTime = 0;

// Setup for HTTP Server and WebSocket. Detects key input, and stores the last timestamp that it was received.
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

// Returns a non-empty character input if lastMessageTime is less than 200 ms ago (Roughly two missed cycles)

// Example: Pressing and holding "W" will return W indefinitely.  Once 2 cycles of inputs has not been detected,  return '\0'
char getInputCharacter() {

    if (millis() - lastMessageTime >  200) {
        storedCharacter = '\0';
    }

    return storedCharacter;

}
