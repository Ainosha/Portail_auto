#ifndef NETWORK_H
#define NETWORK_H

#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#define WLAN_SSID       "OnePlus 8T"
#define WLAN_PASS       "Jaibesoins4g"

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL

#define AIO_USERNAME    ""
#define AIO_KEY         ""

#define DELAY_MQTT_PROCESS 5000

static bool init_MQTT();
void init_WIFI();
bool MQTT_disconnect();
bool send_mqtt(int data);
String process_read_mqtt(int delay);


#endif