#ifndef PORTAIL_DIGI_H
#define PORTAIL_DIGI_H

#include <Keypad.h>
#include <ESP32Servo.h>  // Utilisation de la bibliothèque ESP32Servo

// Déclaration des variables pour le clavier
extern char keys[4][4];
extern byte rowPins[4];
extern byte colPins[4];

// Prototypes des fonctions
void openGate();
void moveServoWithBlink(int startPos, int endPos, int moveDuration);
String getpad();

#endif
