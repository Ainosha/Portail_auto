#ifndef PORTAIL_DIGI_H
#define PORTAIL_DIGI_H

#include <Keypad.h>
#include <ESP32Servo.h>  // Utilisation de la bibliothèque ESP32Servo

// Déclaration des constantes pour le clavier matriciel
extern const int ROWS;
extern const int COLS;

// Déclaration des variables pour le clavier
extern char keys[4][4];
extern byte rowPins[4];
extern byte colPins[4];

// Déclaration des autres variables globales
extern Servo myservo;
extern Keypad keypad;
extern String inputCode;
extern const String correctCode;

// Déclaration des pins pour les LEDs et le servo
extern const int servoPin;
extern const int ledBuiltin;
extern const int yellowLedPin;

// Prototypes des fonctions
void openGate();
void moveServoWithBlink(int startPos, int endPos, int moveDuration);

#endif
