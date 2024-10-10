#ifndef WAKEUP_PROCESS_H
#define WAKEUP_PROCESS_H

#include <Arduino.h>
#include <buzzer_song.h>
#include <driver/adc.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <wakeup_process.h>
#include <RFID.h>
#include <portail_digi.h>
#include <Network.h>

const int ledPin = 2;  // Use GPIO 2 for built-in LED (on many ESP32 boards)
const int sensorPin = 36;  // GPIO36 is the VP pin
const int sensorPinVN = 39;  // GPIO39 is the VN pin
const int buttonpin = 0;

#define PasswordPAD     "1234"
#define PasswordUID     "1234"

#define maxAttempts 500

void wakeup_process();
void setup_wakeup_process();

#endif