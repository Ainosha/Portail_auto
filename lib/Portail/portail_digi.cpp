#include <portail_digi.h>


String inputCode = "";
Servo myservo;
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void portail_init(){

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

void getpad(){
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
  blink(yellowLedPin);
  myservo.write(90);   // Ouvrir le portail (90°)
  delay(3000);         // Garder ouvert pendant 3 secondes
  blink(yellowLedPin);
  myservo.write(0);    // Fermer le portail (0°)
}

void blink(int Pin) {
  for (int i = 0; i < 6; i++) {
    digitalWrite(Pin, HIGH);
    delay(250);
    digitalWrite(Pin, LOW);
    delay(250);
  }
}
