#include <Arduino.h>
#include <adc_deep_sleep.h>
#include <buzzer_song.h>
#include <wakeup_process.h>
#include <RFID.h>
#include <portail_digi.h>


void setup() {
  Serial.begin(115200);

  // put your setup code here, to run once:
  setup_wakeup_process();
  setup_adc_deep_sleep();
}

void loop() {
  // put your main code here, to run repeatedly:
}