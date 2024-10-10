#include "portail_digi.h"

// Définition des constantes et variables
const int ROWS = 4;
const int COLS = 4;
String inputCodes = "";  // Global variable to store the input code

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {13, 12, 14, 27};  // Connexion des lignes du clavier
byte colPins[COLS] = {26, 25, 33, 32};  // Connexion des colonnes du clavier

// Variables pour le digicode
Servo myservo;
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
const String correctCode = "1234";

// Pins pour les LEDs et le servo
const int servoPin = 5;
const int ledBuiltin = 2;
const int yellowLedPin = 18;

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

String getpad() {
    char key = keypad.getKey();  // Read the key pressed on the keypad

    if (key) {  // Check if a key is pressed
        Serial.println(key);  // Print the key to the serial monitor for debugging

        if (key == '#') {  // Check if '#' is pressed to validate the code
            if (inputCodes.length() == 0) {
                Serial.println("No code entered.");  // Handle the case of no code
                String returnValue = "RFID";  // Prepare to return empty
                inputCodes = "";  // Reset inputCodes
                return returnValue;  // Return empty if no code was entered
            }
            Serial.print("Input code entered: ");
            Serial.println(inputCodes);  // Print the entered code

            String returnValue = inputCodes;  // Store the current inputCodes for returning
            inputCodes = "";  // Reset inputCodes before returning
            return returnValue;  // Return the entered code
        } else if (key == '*') {
            Serial.println("Input cleared.");  // Indicate input cleared
            inputCodes = "";  // Clear the input code
            return "";  // Return empty
        } else {
            // Add the pressed key to the input code
            inputCodes += key;  
        }
    }
    return "";  // Return empty if no key was pressed
}


