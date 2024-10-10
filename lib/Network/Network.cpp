#include <Network.h>

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// Setup a feed called 'photocell' for publishing.
Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/photocell");

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/onoff");
Adafruit_MQTT_Subscribe *subscription;

bool init_WIFI(int after_n500_ms)
{
  /* 
    Connect to WiFi access point.
  */
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  int i=0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    i++;
    if(i>after_n500_ms){
        return false;
    }
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
  return true;
}

static bool init_MQTT() {
    /*
        Connect to server mqtt
    */
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      return false;
    }
  }
  Serial.println("MQTT Connected!");
  return true;
}
bool MQTT_disconnect(){
    return mqtt.disconnect();
}

bool send_mqtt(int data) {
  //Send message to Controleur
  return photocell.publish(data);
}

char process_read_mqtt(int delay) {
  mqtt.processPackets();
    while ((subscription = mqtt.readSubscription(delay))) {
    if (subscription == &onoffbutton) {
      Serial.print(F("Got: "));
      Serial.println((char *)onoffbutton.lastread);
      return (char *)onoffbutton.lastread;
    }
  }
}