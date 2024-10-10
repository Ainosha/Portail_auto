#ifndef PORTAIL_DIGI_H
#define PORTAIL_DIGI_H

#include <Keypad.h>
#include <ESP32Servo.h> // Bibliothèque Servo compatible ESP32
// Définir le clavier matriciel
#define ROWS  4 // 4 lignes
#define COLS  4 // 4 colonnes

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {13, 12, 14, 27};  // Connecter les lignes du clavier
byte colPins[COLS] = {26, 25, 33, 32};  // Connecter les colonnes du clavier

// LED RGB sur 3 pins
#define ledRedPin       15
#define ledGreenPin     2
#define ledBluePin      4

//servo pin 
#define servoPin        5

// LED jaune
#define yellowLedPin    18

// Variables pour le digicode
#define correctCode     "1234" // Code correct

void getpad();
void blink(int Pin);
void openGate();

#endif