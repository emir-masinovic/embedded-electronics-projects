#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {D0, D5, D6, D7}; 
byte colPins[COLS] = {3, 1, D3, D4}; // Rx, Tx, D3, D4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Press any key...");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Key Pressed:");
    lcd.setCursor(2, 1);
    lcd.print(">>   ");
    lcd.print(key);
    lcd.print("   <<");
  }
}