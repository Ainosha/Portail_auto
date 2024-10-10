#include <Keypad.h>
#include <ESP32Servo.h> // Bibliothèque Servo compatible ESP32

// Définir le clavier matriciel
const byte ROWS = 4; // 4 lignes
const byte COLS = 4; // 4 colonnes
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {13, 12, 14, 27};  // Connecter les lignes du clavier
byte colPins[COLS] = {26, 25, 33, 32};  // Connecter les colonnes du clavier

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// LED RGB sur 3 pins
const int ledRedPin = 15;
const int ledGreenPin = 2;
const int ledBluePin = 4;

// Servo moteur
Servo myservo;
const int servoPin = 5;

// LED jaune
const int yellowLedPin = 18;

// Variables pour le digicode
String inputCode = "";
const String correctCode = "1234"; // Code correct

void setup() {
  Serial.begin(115200);

  // Initialisation des LEDs
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledBluePin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);

  // Initialisation du servo
  myservo.attach(servoPin);
  myservo.write(0); // Position fermée

  // LEDs éteintes au départ
  digitalWrite(ledRedPin, LOW);
  digitalWrite(ledGreenPin, LOW);
  digitalWrite(ledBluePin, LOW);
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    Serial.println(key);
    if (key == '#') {
      // Vérifier si le code est correct
      if (inputCode == correctCode) {
        digitalWrite(ledGreenPin, HIGH); // LED verte si le code est correct
        digitalWrite(ledRedPin, LOW);
        digitalWrite(ledBluePin, LOW);

        // Ouvrir le portail
        openGate();
      } else {
        digitalWrite(ledRedPin, HIGH); // LED rouge si le code est incorrect
        digitalWrite(ledGreenPin, LOW);
        digitalWrite(ledBluePin, LOW);
      }
      inputCode = ""; // Réinitialiser le code
    } else if (key == '*') {
      inputCode = ""; // Réinitialiser le code
    } else {
      inputCode += key; // Ajouter le chiffre entré
    }
  }
}

void openGate() {
  blinkYellowLed();
  myservo.write(90);   // Ouvrir le portail (90°)
  delay(3000);         // Garder ouvert pendant 3 secondes
  blinkYellowLed();
  myservo.write(0);    // Fermer le portail (0°)
}

void blinkYellowLed() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(yellowLedPin, HIGH);
    delay(250);
    digitalWrite(yellowLedPin, LOW);
    delay(250);
  }
}
