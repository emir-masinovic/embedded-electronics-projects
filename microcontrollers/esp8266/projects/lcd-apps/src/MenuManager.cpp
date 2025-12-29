#include "MenuManager.h"
#include "MenuView.h"
#include "keypad_config.h"
#include "apps.h"
#include "icons.h"
#include "WeatherApp.h"

namespace MenuManager {

    enum SystemState { STATE_MENU, APP_WEATHER, APP_DINO, APP_CONSOLE };
    static SystemState currentSystemState = STATE_MENU;

    struct MenuModel {
        int currentIndex = 0;
        const int totalApps = 3;
        const char* appNames[3] = {"WEATHER", "DINO", "CONSOLE"};
    };

    static MenuModel model;
    LiquidCrystal_I2C lcd(0x27, 16, 2);

    void processEvents(char key);

    void init() {
        lcd.init();
        lcd.backlight();
        lcd.createChar(0, (uint8_t*)icon_weather);
        lcd.createChar(1, (uint8_t*)icon_dragon);
        lcd.createChar(2, (uint8_t*)icon_console);
        MenuView::draw(lcd, model.currentIndex, model.totalApps, model.appNames);
    }

    void run() { processEvents(keypad.getKey()); }

    void processEvents(char key) {

        if (currentSystemState == STATE_MENU) {
            if (!key) return;
            bool moved = false;

            if (key == 'A') { model.currentIndex = (model.currentIndex - 1 + model.totalApps) % model.totalApps; moved = true; }
            if (key == 'B') { model.currentIndex = (model.currentIndex + 1) % model.totalApps; moved = true; }
            if (key == 'C') { // C means enter app
                currentSystemState = (SystemState)(model.currentIndex + 1); 
                currentAppStatus = APP_RUNNING;
                lcd.clear();

                // Single init call (avoiding rerun)
                if (currentSystemState == APP_WEATHER) WeatherApp::init(lcd);
            }

            // Only a single update call for the screen
            if (moved) MenuView::draw(lcd, model.currentIndex, model.totalApps, model.appNames);
            return;
        }

        switch (currentSystemState) {
            case APP_WEATHER:
                WeatherApp::run(key, lcd);
                break;

            case APP_DINO:
                lcd.setCursor(0,0); lcd.print("Dino App...");
                break;

            case APP_CONSOLE:
                lcd.setCursor(0,0); lcd.print("Console App...");
                break;
            
            default: break;
        }

        // D is global exit for now
        if (key == 'D') { 
            currentAppStatus = APP_EXIT; 
        }

        if (currentAppStatus == APP_EXIT) {
            currentSystemState = STATE_MENU;
            MenuView::draw(lcd, model.currentIndex, model.totalApps, model.appNames);
        }
    }
}