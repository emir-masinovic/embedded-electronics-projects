#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "keypad_config.h"
#include "icons.h"
#include "apps.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

int currentMenuIdx = 0;
const int totalApps = 3;
String appNames[] = {"WEATHER", "DINO", "CONSOLE"};

// Forward declarations
void drawMenu();
void handleMenuNavigation(char key);

void setup() {
    lcd.init();
    lcd.backlight();

    // Load menu icons into slots 0, 1, 2 (used by write of some index)
    // LCD can only hold 8 icons at a time apparently
    lcd.createChar(0, (uint8_t*)icon_weather);
    lcd.createChar(1, (uint8_t*)icon_dragon);
    lcd.createChar(2, (uint8_t*)icon_console);
    
    drawMenu();
}

void loop() {
    char key = keypad.getKey();

    if (currentState == STATE_MENU) {
        handleMenuNavigation(key); 
    } else {
        dispatchApp(key, lcd);

        if (currentState == STATE_MENU) { drawMenu(); }
    }
}

void handleMenuNavigation(char key) {
    if (!key) return;

    if (key == 'A') { // Scroll Left
        currentMenuIdx = (currentMenuIdx - 1 + totalApps) % totalApps;
        drawMenu();
    } 
    else if (key == 'B') { // Scroll Right
        currentMenuIdx = (currentMenuIdx + 1) % totalApps;
        drawMenu();
    }
    else if (key == 'C') { // Enter Selection
        if (currentMenuIdx == 0) currentState = STATE_WEATHER;
        else if (currentMenuIdx == 1) currentState = STATE_DINO;
        else if (currentMenuIdx == 2) currentState = STATE_CONSOLE;
        lcd.clear();
    }
}

void drawMenu() {
    lcd.clear();

    // Row 1: Logo and centered App Name
    int titlePos = (16 - appNames[currentMenuIdx].length()) / 2;
    lcd.setCursor(0, 0); lcd.write(currentMenuIdx);
    lcd.setCursor(titlePos, 0); lcd.print(appNames[currentMenuIdx]);
    
    // Row 2: Carousel of icons (Denser information. Odd numbers are great for alignment)
    int prev = (currentMenuIdx - 1 + totalApps) % totalApps;
    int next = (currentMenuIdx + 1) % totalApps;

    lcd.setCursor(0,  1); lcd.print("<     [ ]     > ");
    lcd.setCursor(3,  1); lcd.write(prev);
    lcd.setCursor(7,  1); lcd.write(currentMenuIdx); 
    lcd.setCursor(11, 1); lcd.write(next);
}