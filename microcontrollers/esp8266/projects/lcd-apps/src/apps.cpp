#include "apps.h"

AppStatus currentAppStatus = APP_RUNNING;

void dispatchApp(char key, LiquidCrystal_I2C &lcd) {

    lcd.setCursor(0,0); lcd.print("Running App...");
    
    if (key == 'D') {
        currentAppStatus = APP_EXIT;
    }
}