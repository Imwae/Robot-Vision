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

static const char *htmlContent PROGMEM = R"rawliteral(
    <!doctype html>
    <html>
        <head>
            <meta charset="utf-8"/>
            <title>RobotMovement</title>
        </head>
        <body>

        <p id="textSpace">
            Control movement: 

        </p>

        <button type="button" id="toggleButton">
            Control movement toggle
        </button>

        <button type="button" id="retryConnection">
            Retry connection
        </button>

        <script>
            let keyInput = ""
            let controlEnabled = false
            const toggleButton = document.getElementById("toggleButton")
            const textStatus = document.getElementById("textSpace")
            const retryConnection = document.getElementById("retryConnection")
            const primaryHost = window.location.hostname
            const fallbackIp= "10.0.0.71"
            const host = primaryHost || fallbackIp
            let ws
            connectSocket()

            function connectSocket() {
                ws = new WebSocket("ws://" + host + "/ws")

                ws.onclose = function showButton() {
                    retryConnection.style.display = "block"
                }

                ws.onopen = function hideButton() {
                    retryConnection.style.display = "none"
                }
            }

            setInterval(function() {
                if ((keyInput !== "") && (ws.readyState === WebSocket.OPEN)) {
                    console.log(keyInput) 
                    ws.send(keyInput)
                }
                
            }, 100)

            toggleButton.addEventListener("click", function(event) {
                controlEnabled = !controlEnabled
                textStatus.textContent = "Control movement toggle: " + controlEnabled

                if (!controlEnabled) {
                    keyInput = ""
                }
            })

            retryConnection.addEventListener("click", function(event) {
                connectSocket()
            })

            document.addEventListener("keydown", function(event) {
                if (controlEnabled) {
                    keyInput = (event.key).toUpperCase()
                }
            })

            document.addEventListener("keyup", function(event) {
                if (keyInput === (event.key).toUpperCase()) {
                    keyInput = ""
                    console.log("Keypress ended!")
                }
            })

        </script>
        </body>
    </html>

)rawliteral";

// Setup for HTTP Server and WebSocket. Detects key input, and stores the last timestamp that it was received.
void setupWebPage() {

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html", htmlContent);
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
