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

static void blinkCount(int count) {
    for (int i = 0; i < count; i++) {
        powerLow();
        delay(100);
        powerHigh();
        delay(100);
    }
}

void blinkSuccess() {
    blinkCount(4);
}
void blinkFailed()  {
    blinkCount(2);
}
void blinkAttemptConnect() {
    powerLow();
    delay(500);
    powerHigh();
    delay(500);
}