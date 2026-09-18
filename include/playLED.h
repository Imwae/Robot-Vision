#ifndef PLAYLED_H
#define PLAYLED_H

void setupLEDPin();

void powerHigh(int pin);
void powerLow(int pin);

void blinkSuccess();
void blinkFailed();
void blinkAttemptConnect();

#endif