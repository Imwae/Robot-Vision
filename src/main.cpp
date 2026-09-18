#include <Arduino.h>
#include "wirelessManager.h"

int PIN_NUMBER = 46; // RGB Pin

// Motor Driver Connection Pins
const int PIN_AIN1 = D3;
const int PIN_AIN2 = D4;
const int PIN_PWMA = D5;
const int PIN_BIN1 = D6;
const int PIN_BIN2 = D7;
const int PIN_PWMB = D8;

// put function declarations here:
void powerHigh(int);
void powerLow(int);
void delayOneSecond();

void motorDrive();
void motorForward();
void motorBackward();
void motorLeft();
void motorRight();
void stopMotor(int, int, int);

void setMotor(int, int, int, bool, int);
void setupMotorPins();
void setupNetwork();

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(PIN_NUMBER, OUTPUT);

    delayOneSecond();
    
    setupMotorPins();
    setupNetwork();


}

void loop() {
  // put your main code here, to run repeatedly:

  motorDrive();
}

// put function definitions here:

// setup functions

void setupNetwork() {

    if (connectNetwork()) {
        Serial.println("Connected!");
    } else {
        Serial.println("Unsuccessful! Try again!");
    }
}

void setupMotorPins() {
    pinMode(PIN_AIN1, OUTPUT);
    pinMode(PIN_AIN2, OUTPUT);
    pinMode(PIN_PWMA, OUTPUT);
    pinMode(PIN_BIN1, OUTPUT);
    pinMode(PIN_BIN2, OUTPUT);
    pinMode(PIN_PWMB, OUTPUT);
}

// Blinking light functions
void powerHigh(int pin) {
  digitalWrite(pin, HIGH);
}

void powerLow(int pin) {
  digitalWrite(pin, LOW);
}

void delayOneSecond() {
  delay(1000);
}

// Car movement functions

void setMotor(int pinIn1, int pinIn2, int pinPWM, bool forward, int speed) {

    analogWrite(pinPWM, speed);

    if (forward) {
        digitalWrite(pinIn1, HIGH);
        digitalWrite(pinIn2, LOW);
    } else {
        digitalWrite(pinIn1, LOW);
        digitalWrite(pinIn2, HIGH);
    }

}

void motorDrive() {
    if (Serial.available() > 0) {
        char key = Serial.read();
        key = toupper(key);

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
            
            case 'X':
                stopMotor(PIN_AIN1, PIN_AIN2, PIN_PWMA);
                stopMotor(PIN_BIN1, PIN_BIN2, PIN_PWMB);
                break;
        }
    }
}

void motorForward() {
    setMotor(PIN_AIN1,PIN_AIN2, PIN_PWMA, true, 100);
    setMotor(PIN_BIN1,PIN_BIN2, PIN_PWMB, true, 100);
}

void motorBackward() {
    setMotor(PIN_AIN1,PIN_AIN2, PIN_PWMA, false, 100);
    setMotor(PIN_BIN1,PIN_BIN2, PIN_PWMB, false, 100);
}

void motorLeft() {
    setMotor(PIN_AIN1,PIN_AIN2, PIN_PWMA, true, 100);
    setMotor(PIN_BIN1,PIN_BIN2, PIN_PWMB, false, 100);
}

void motorRight() {
    setMotor(PIN_AIN1,PIN_AIN2, PIN_PWMA, false, 100);
    setMotor(PIN_BIN1,PIN_BIN2, PIN_PWMB, true, 100);
}

void stopMotor(int pinIn1, int pinIn2, int pinPWM) {
    digitalWrite(pinIn1, LOW);
    digitalWrite(pinIn2, LOW);
    analogWrite(pinPWM, 0);
}
