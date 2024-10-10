#include <RFID.h>

MFRC522 rfid(SS_PIN, RST_PIN);


String read_rfid() {
  String uidString = ""; // Initialisation d'une chaîne pour l'UID
  if(rfid.PICC_IsNewCardPresent()){
    if (rfid.PICC_ReadCardSerial()) { // Tente de lire le NUID
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
      Serial.print("RFID/NFC Tag Type: ");
      Serial.println(rfid.PICC_GetTypeName(piccType));

      // Construction de l'UID au format hexadécimal
      Serial.print("UID: ");
      for (int i = 0; i < rfid.uid.size; i++) {
        if (rfid.uid.uidByte[i] < 0x10) {
          uidString += "0"; // Ajoute un zéro pour un format uniforme
        }
        uidString += String(rfid.uid.uidByte[i], HEX); // Convertit l'octet en hexadécimal
      }
      Serial.println(uidString); // Affiche l'UID sur le moniteur série

      rfid.PICC_HaltA(); // Met la carte en pause
      rfid.PCD_StopCrypto1(); // Arrête le chiffrement
    } else {
      Serial.println("Erreur: Impossible de lire le NUID de la carte.");
    }
  }
  return "Fail"; // Retourne l'UID
}

