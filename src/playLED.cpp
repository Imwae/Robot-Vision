/*

Functions relating to Arduino Nano ESP32S3's on-board LED.  Below are some of the types of LED visuals that I have used

The pin works in a LOW setting, so powerLow() so  writing the pin to low turns on the LED, and vise versa

*/

#include "playLED.h"
#include <Arduino.h>

const int PIN_NUMBER = 46; // RGB Pin

// blinking setup
void setupLEDPin() {
    pinMode(PIN_NUMBER, OUTPUT);
}
static void powerHigh() {
    digitalWrite(PIN_NUMBER, HIGH);
}
static void powerLow() {
    digitalWrite(PIN_NUMBER, LOW);
}

// types of blinks

void ledOn() {
    powerLow();
}

void ledOff() {
    powerHigh();
}

// blinks the LED n times (depending on count)

static void blinkCount(int count) {
    for (int i = 0; i < count; i++) {
        powerLow();
        delay(100);
        powerHigh();
        delay(100);
    }
}

// number of blinks when connnction to the network was successful

void blinkSuccess() {
    blinkCount(4);
}

// number of blinks when connnction to the network has failed
void blinkFailed()  {
    blinkCount(2);
}

// number of blinks when connnction to the network is retrying / attempting to connect  NOTE: The blinking on initialization is the only time it does not work.
void blinkAttemptConnect() {
    powerLow();
    delay(500);
    powerHigh();
    delay(500);
}