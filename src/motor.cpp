/*

motor handles all of the motor functions and movements


Initializes the motor pins to support output, and supports motors that drive in all four directions including stop

Motors is linked up via TB6612FNG motor driver chip, which is wired to the Arduino nano ESP32S3 board

(TEMP WORKAROUND FOR A PROBLEM):    delay(100) because motors pull in a surge of current when starting up, which the battery pack I am operating now 
                                    cannnot handle.  Delay helps with voltage not sagging below the required current for the two motors
*/

#include <Arduino.h>
#include "motor.h"

// Motor Driver Connection Pins
const int PIN_AIN1 = D3;
const int PIN_AIN2 = D4;
const int PIN_PWMA = D5;
const int PIN_BIN1 = D6;
const int PIN_BIN2 = D7;
const int PIN_PWMB = D8;


// Car movement functions

void setupMotorPins() {
    pinMode(PIN_AIN1, OUTPUT);
    pinMode(PIN_AIN2, OUTPUT);
    pinMode(PIN_PWMA, OUTPUT);
    pinMode(PIN_BIN1, OUTPUT);
    pinMode(PIN_BIN2, OUTPUT);
    pinMode(PIN_PWMB, OUTPUT);
}

// Sets the motor pins in the specified order according to the schematics, according to direction and speed
static void setMotor(int pinIn1, int pinIn2, int pinPWM, bool forward, int speed) {

    analogWrite(pinPWM, speed);

    if (forward) {
        digitalWrite(pinIn1, HIGH);
        digitalWrite(pinIn2, LOW);
    } else {
        digitalWrite(pinIn1, LOW);
        digitalWrite(pinIn2, HIGH);
    }

}

// spins both motors forwards

void motorForward() {
    setMotor(PIN_BIN1,PIN_BIN2, PIN_PWMB, true, 100);
    delay(100);
    setMotor(PIN_AIN1,PIN_AIN2, PIN_PWMA, true, 100);
}

// spins both motors backwards
void motorBackward() {
    setMotor(PIN_AIN1,PIN_AIN2, PIN_PWMA, false, 100);
    delay(100);
    setMotor(PIN_BIN1,PIN_BIN2, PIN_PWMB, false, 100);
}

// spins motor A forward, while the motor B backwards
void motorLeft() {
    setMotor(PIN_AIN1,PIN_AIN2, PIN_PWMA, true, 100);
    delay(100);
    setMotor(PIN_BIN1,PIN_BIN2, PIN_PWMB, false, 100);
}

// spins the motor A backwards, while the motor B forwards
void motorRight() {
    setMotor(PIN_AIN1,PIN_AIN2, PIN_PWMA, false, 100);
    delay(100);
    setMotor(PIN_BIN1,PIN_BIN2, PIN_PWMB, true, 100);
}

// configures the motor pins to low setting, which stops the motors from moving
static void stopMotor(int pinIn1, int pinIn2, int pinPWM) {
    digitalWrite(pinIn1, LOW);
    digitalWrite(pinIn2, LOW);
    analogWrite(pinPWM, 0);
}

// stops both motors
void stopBothMotors() {
    stopMotor(PIN_AIN1, PIN_AIN2, PIN_PWMA);
    stopMotor(PIN_BIN1, PIN_BIN2, PIN_PWMB);

}