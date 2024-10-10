#include <wakeup_process.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

static void LCD_display(int tempo);
static void LCD_off();

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
  //init led
  pinMode(LED_BUILTIN, OUTPUT);
  // capteur
  pinMode(sensorPin, INPUT);  // Set the VP pin as an input
  pinMode(sensorPinVN, INPUT);  // Set the VN pin as an input
}

void wakeup_process()
{
  do 
  {
    // affichage LCD
    LCD_display(100);
  } while(analogRead(sensorPin) > 1500);
  LCD_off();
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
