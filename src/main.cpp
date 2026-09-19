#include <Arduino.h>
#include "wirelessManager.h"
#include "playLED.h"
#include "webManager.h"
#include "motor.h"


// put function declarations here:
void delayOneSecond();

// void wiredMotorDrive(); // unused method
void wirelessMotorDrive();

void setupNetwork();

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    setupLEDPin();

    delayOneSecond();

    setupMotorPins();
    setupNetwork();
}

void loop() {
    // put your main code here, to run repeatedly:

    if (checkConnection()) {
        // wiredMotorDrive(); This is when the robot is connected via USB
        wirelessMotorDrive(); // This is when the robot is connected via Network
    } else {
        stopBothMotors();
        blinkAttemptConnect();
    }
}

// put function definitions here:

void delayOneSecond() {
  delay(1000);
}

// setup functions

void setupNetwork() {

    if (connectNetwork()) {
        Serial.println("Connected!");
        blinkSuccess();
        setupWebPage();

    } else {
        Serial.println("Unsuccessful! Try again!");
        blinkFailed();
    }
}

// Motor functions

// void wiredMotorDrive() {
//     if (Serial.available() > 0) {
//         char key = Serial.read();
//         key = toupper(key);

//         switch (key) {
//             case 'W':
//                 motorForward();
//                 break;
//             case 'A':
//                 motorLeft();
//                 break;
//             case 'S':
//                 motorBackward();
//                 break;
//             case 'D':
//                 motorRight();
//                 break;
            
//             case 'X':
//                 stopBothMotors();
//                 break;
//         }
//     }
// }

// Current working wireless movements

void wirelessMotorDrive() {
    char key = getInputCharacter();
    key = toupper(key);

    if (key != '\0') {
        ledOn();
    } else {
        ledOff();
    }

    switch (key) {

        case 'W':
            motorForward();
            break;
        case 'A':
            motorLeft();
            break;
        case 'S':
            motorBackward();
            break;
        case 'D':
            motorRight();
            break;

        default:
            stopBothMotors();
            break;
    }
}
