# Projet Portail Automatique

**Cours** : Objets Connectés Basse Consommation  
**Auteur** : Théo LEBLANC, Eric PAN, Maxime JANNEZ, Thomas SEGARD
**Date** : 10/2024

## Description du projet

Ce projet consiste à la réalisation d'un **portail automatique** contrôlé via un **digicode**, un **capteur de présence infrarouge**, et une fonctionnalité de **contrôle à distance** avec des notifications via **WhatsApp**. Le système est conçu pour être **économe en énergie**, s'activant uniquement en présence d'une personne. Un écran LCD affiche des informations sur le portail et le statut du système. Le projet a été développé dans le cadre du cours "Objets Connectés Basse Consommation".

### Fonctionnalités principales

- **Détection de présence** : Un **capteur infrarouge** détecte la présence d'une personne devant le portail, ce qui active le système.
- **Afficheur LCD** : Lorsque la présence est détectée, l'écran **LCD** s'allume et affiche des messages concernant l'état du portail.
- **Contrôle par digicode** : L'ouverture du portail est activée par l'entrée d'un code correct via un clavier matriciel.
- **Ouverture/fermeture avec servo moteur** : Un **servo moteur** simule l'ouverture et la fermeture du portail.
- **Notifications WhatsApp** : Un message est envoyé au propriétaire via WhatsApp lorsqu'une présence est détectée ou lorsque quelqu'un appuie sur un bouton.
- **API pour autorisation à distance** : Le propriétaire peut répondre au message WhatsApp pour autoriser ou refuser l'ouverture du portail à distance.
- **LED de contrôle** :
  - **LED intégrée (ESP32)** : S'allume pendant 3 secondes lorsque le bon code est saisi.
  - **LED jaune** : Clignote pendant que le portail s'ouvre ou se ferme.
- **Temporisation** : Une temporisation de 5 secondes est appliquée après l'ouverture du portail avant qu'il ne commence à se refermer, pendant laquelle la LED est éteinte.

## Matériel utilisé

- **ESP32 NodeMCU-32S**
- **Clavier matriciel 4x4** (Keypad)
- **Servo moteur** (alimenté en 5V)
- **Afficheur LCD** (compatible I2C pour économie de pins)
- **Capteur infrarouge** (PIR sensor) pour la détection de présence
- **LED jaune** (pour indiquer le mouvement du portail)
- **Bouton poussoir** (pour actionner manuellement le portail)
- **Résistances** (220Ω pour la LED)
- Câblage et breadboard

## Schéma de câblage

Le schéma de câblage est disponible dans le dossier `fritzing_schematics`. Il montre les connexions des différents composants avec la carte ESP32, incluant les pins pour le servo, le clavier matriciel, le capteur infrarouge et l'écran LCD.

### Connexions principales :

- **Servo moteur** :
  - Signal → GPIO 5
  - Alimentation → 5V
  - GND → GND

- **Keypad** :
  - Lignes → GPIO 13, 12, 14, 27
  - Colonnes → GPIO 26, 25, 33, 32

- **LED jaune** :
  - Anode → GPIO 18
  - Cathode → GND (avec résistance 220Ω)

- **Capteur infrarouge (PIR)** :
  - Signal → GPIO [À définir]
  - Alimentation → 5V
  - GND → GND

- **Afficheur LCD (I2C)** :
  - SDA → GPIO 21
  - SCL → GPIO 22
  - Alimentation → 5V
  - GND → GND

## Fonctionnement

1. **Détection de présence** : Le capteur infrarouge (PIR) détecte une présence et active le système.
   - L'afficheur **LCD** s'allume et affiche un message d'accueil ou des informations sur l'état du portail.
   - Un message **WhatsApp** est envoyé au propriétaire pour l'alerter de la présence détectée.

2. **Contrôle par digicode** : L'utilisateur entre un code à 4 chiffres via le clavier matriciel.
   - Si le code est correct (`1234` par défaut), la **LED intégrée de l'ESP32** s'allume pendant 3 secondes, et le portail s'ouvre.

3. **Ouverture du portail** : Le servo moteur se déplace de 0° à 90° pour ouvrir le portail, tout en faisant clignoter la **LED jaune**.

4. **Temporisation** : Après l'ouverture, il y a une pause de **5 secondes** où la **LED jaune est éteinte**.

5. **Fermeture du portail** : Après la temporisation, le portail se referme et la **LED jaune** clignote pendant ce mouvement.

6. **Notifications WhatsApp et API de contrôle à distance** :
   - Si une personne appuie sur le bouton, une notification est envoyée via **WhatsApp**.
   - Le propriétaire peut répondre à ce message pour autoriser ou refuser l'ouverture à distance du portail via une API dédiée.

## Installation

1. **Clonez ce dépôt** sur votre machine locale :

```bash
git clone https://github.com/Ainosha/Portail_auto.git
```

2. **Téléversez le code** sur l'ESP32 via l'IDE Arduino ou PlatformIO.

3. **Branchez les composants** comme indiqué dans le schéma Fritzing.

4. **Installez les bibliothèques nécessaires** via le gestionnaire de bibliothèques Arduino ou PlatformIO.

## Bibliothèques nécessaires

- **Keypad** : Pour gérer le clavier matriciel.
- **ESP32Servo** : Pour contrôler le servo moteur avec l'ESP32.
- **LiquidCrystal_I2C** : Pour gérer l'écran LCD via I2C.
- **PubSubClient** (ou équivalent) : Pour gérer les messages WhatsApp et l'API de contrôle à distance.

## API de contrôle à distance

L'API permet de recevoir des messages et des réponses via WhatsApp pour autoriser l'ouverture du portail. Le propriétaire peut envoyer une commande d'autorisation, et le système ouvrira le portail à distance si l'autorisation est accordée.

## Auteurs

- Théo LEBLANC, Eric PAN, Maxime JANNEZ, Thomas SEGARD - Étudiant en 5A à L'ESIEA, Cours Objets Connectés Basse Consommation

## Remerciements

- Merci à M COURBIN pour l'encadrement de ce projet.
