#ifndef WAKEUP_PROCESS_H
#define WAKEUP_PROCESS_H

#include <Arduino.h>
#include <buzzer_song.h>
#include <Arduino.h>
#include <driver/adc.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int ledPin = 2;  // Use GPIO 2 for built-in LED (on many ESP32 boards)
const int sensorPin = 36;  // GPIO36 is the VP pin
const int sensorPinVN = 39;  // GPIO39 is the VN pin

void wakeup_process();
void setup_wakeup_process();

#endif