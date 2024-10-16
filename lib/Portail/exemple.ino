include <Keypad.h>
#include <ESP32Servo.h>  // Utilisation de la bibliothèque ESP32Servo

// Configuration du Keypad (clavier matriciel)
const byte ROWS = 4; // 4 lignes
const byte COLS = 4; // 4 colonnes
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {13, 12, 14, 27};  // Connexion des lignes du clavier
byte colPins[COLS] = {26, 25, 33, 32};  // Connexion des colonnes du clavier

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Servo moteur
Servo myservo;          // Créer un objet Servo
const int servoPin = 5;  // Pin pour contrôler le servo
int minUs = 500;         // Minimum pulse width en microsecondes
int maxUs = 2400;        // Maximum pulse width en microsecondes

// LED intégrée de l'ESP32
const int ledBuiltin = 2;  // LED intégrée (GPIO 2)

// LED jaune
const int yellowLedPin = 18;  // Pin pour la LED jaune

// Variables pour le code du digicode
String inputCode = "";
const String correctCode = "1234";  // Le code correct à entrer

void setup() {
  Serial.begin(115200);
  
  // Initialisation des LEDs et du servo
  pinMode(ledBuiltin, OUTPUT);  // LED intégrée
  pinMode(yellowLedPin, OUTPUT);  // LED jaune

  // Initialisation du servo en utilisant minUs et maxUs pour définir les limites des impulsions
  myservo.attach(servoPin, minUs, maxUs);
  myservo.writeMicroseconds(minUs);  // Position fermée au début

  // Éteindre toutes les LEDs au départ
  digitalWrite(ledBuiltin, LOW);
  digitalWrite(yellowLedPin, LOW);
}

void loop() {
  char key = keypad.getKey();  // Lire la touche pressée sur le Keypad
  
  if (key) {
    Serial.println(key);  // Afficher la touche sur le moniteur série

    if (key == '#') {  // Vérifier si la touche '#' est pressée pour valider
      if (inputCode == correctCode) {
        // Code correct
        Serial.println("Code correct !");
        digitalWrite(ledBuiltin, HIGH);  // Allumer la LED intégrée
        delay(3000);  // Laisser allumée 3 secondes
        digitalWrite(ledBuiltin, LOW);   // Éteindre la LED

        // Ouvrir le portail
        openGate();
      } else {
        // Code incorrect
        Serial.println("Code incorrect !");
      }
      inputCode = "";  // Réinitialiser le code après la validation
    } else if (key == '*') {
      inputCode = "";  // Réinitialiser le code si '*' est pressé
    } else {
      inputCode += key;  // Ajouter la touche au code en cours de saisie
    }
  }
}

// Fonction pour ouvrir et fermer le portail avec la LED jaune clignotant en parallèle
void openGate() {
  // Ouvrir le portail (90°) avec clignotement de la LED jaune en parallèle
  moveServoWithBlink(0, 90, 3000);  // Passer de 0° à 90° en 3 secondes
  
  // Temporisation de 5 secondes avec LED éteinte
  Serial.println("Temporisation de 5 secondes...");
  digitalWrite(yellowLedPin, LOW);  // Éteindre la LED jaune
  delay(5000);  // Attendre 5 secondes

  // Fermer le portail (0°) avec clignotement de la LED jaune en parallèle
  moveServoWithBlink(90, 0, 3000);  // Passer de 90° à 0° en 3 secondes
}

// Fonction pour déplacer le servo et faire clignoter la LED jaune en même temps
void moveServoWithBlink(int startPos, int endPos, int moveDuration) {
  int steps = 30;  // Diviser le mouvement en 30 étapes
  int stepDelay = moveDuration / steps;  // Délai entre chaque étape

  for (int i = 0; i <= steps; i++) {
    // Calculer la position intermédiaire du servo
    int currentPos = map(i, 0, steps, startPos, endPos);
    myservo.write(currentPos);  // Déplacer le servo à la position intermédiaire

    // Clignoter la LED jaune
    digitalWrite(yellowLedPin, (i % 2 == 0) ? HIGH : LOW);  // Alterner ON/OFF à chaque étape

    delay(stepDelay);  // Attendre avant l'étape suivante
  }
  
  // S'assurer que la LED jaune est éteinte après le mouvement
  digitalWrite(yellowLedPin, LOW);
}