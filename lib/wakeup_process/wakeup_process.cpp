#include <wakeup_process.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

static void LCD_display(int tempo);
static void LCD_off();

volatile bool clickbutton = false;
void interruptbutton();
/* 
ce que je dois setup : 
- ADC GPIO36 (capteur présence)
- buzzer GPIO5
- LCD GPIO (D21 => SDA / D22 => SCL)
*/
void setup_wakeup_process()
{
  //initialize lcd screen
  lcd.init();
  if(!init_WIFI()){
    Serial.print("error Wifi");
  }
  if(!init_MQTT()){
    Serial.print("error MQTT");
  }
  attachInterrupt(digitalPinToInterrupt(buttonpin), interruptbutton, FALLING); // Attach interrupt on falling edge  //init led
  pinMode(LED_BUILTIN, OUTPUT);
  // capteur
  pinMode(sensorPin, INPUT);  // Set the VP pin as an input
  pinMode(sensorPinVN, INPUT);  // Set the VN pin as an input
}

void wakeup_process()
{
  do {
    // affichage LCD
   LCD_display(100);
    
    if (clickbutton == true) {
        send_mqtt("Call from door");
        
        // Wait for a response from MQTT with a timeout of 5000ms
        if (process_read_mqtt(5000) == "Okay") {
            openGate(); // Open the gate if the response is "Okay"
        }
    } 
    else {
        String inputCode = getpad(); // Get code from keypad
        
        if (inputCode == PasswordPAD) {
            openGate(); // Open the gate if the keypad code is correct
        } 
        else if (inputCode == "RFID") {
            String rfida = ""; 
            int attempts = 0;
            // Loop to read RFID until success, maxAttempts is reached, or button is pressed
            while (attempts < maxAttempts && (rfida = read_rfid()) == "Fail") {
                if (clickbutton) { // Check if the interrupt flag is set
                    Serial.println("Button pressed! Exiting RFID process.");
                    return; // Exit the function early if button is pressed
                }
                delay(500);  // Add a delay to avoid spamming the RFID reader
                attempts++;
            }
            
            // If RFID read is successful and matches the expected UID
            if (rfida == PasswordUID) {
                openGate(); // Open the gate
            }
        }
    }
}
  while(analogRead(sensorPin) > 1500);
  LCD_off();
  if(!MQTT_disconnect()){
    Serial.print("error disconnect MQTT");
  }
  if(!wifi_disconnect()){
    Serial.print("error disconnect wifi");
  }
}

void interruptbutton(){
  clickbutton = true;
}

static void LCD_display(int tempo)
{
  lcd.backlight();
  lcd.setCursor(0, 0); 
  lcd.print("Bonjour !");
  //lcd.scrollDisplayRight();
  lcd.setCursor(0, 1);
  lcd.print("Entrer DigiCode");
  delay(tempo);
}

static void LCD_off()
{
  lcd.noBacklight();
  lcd.clear();
}
