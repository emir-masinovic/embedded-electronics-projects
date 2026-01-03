#include "MenuManager.h"
#include "MenuView.h"
#include "keypad_config.h"
#include "apps.h"
#include "icons.h"
#include "WeatherApp.h"
#include "SettingsWifi.h"
#include "utils.h"

namespace MenuManager
{
    using namespace Utils;

    enum SystemState
    {
        STATE_MENU,
        APP_WEATHER,
        APP_DINO,
        APP_CONSOLE,
        SETTINGS_WIFI
    };

    struct MenuModel
    {
        int currentIndex = 0;
        const int totalApps = 4;
        const char *appNames[4] = {"WEATHER", "DINO", "CONSOLE", "WIFI"};
    };

    static MenuModel model;
    static SystemState currentSystemState = STATE_MENU;
    LiquidCrystal_I2C lcd(0x27, 16, 2);

    char globalSsid[33] = "";
    char globalPass[65] = "";

    void handleMenuNavigation(InputAction action);
    void processEvents(char key);

    void init()
    {
        lcd.init();
        lcd.backlight();
        lcd.createChar(0, (uint8_t *)icon_weather);
        lcd.createChar(1, (uint8_t *)icon_dragon);
        lcd.createChar(2, (uint8_t *)icon_console);
        MenuView::draw(lcd, model.currentIndex, model.totalApps, model.appNames);
    }

    void run() { processEvents(keypad.getKey()); }

    void processEvents(char key)
    {
        InputAction action = getAction(key);

        // Global Action: Exit always takes priority
        if (action == ACT_BACK && currentSystemState != STATE_MENU)
        {
            currentSystemState = STATE_MENU;
            lcd.clear();
            MenuView::draw(lcd, model.currentIndex, model.totalApps, model.appNames);
            return;
        }

        // clang-format off
        switch (currentSystemState) {
            case STATE_MENU:     handleMenuNavigation(action); break;
            case APP_WEATHER:    WeatherApp::run(key, lcd);    break;
            case SETTINGS_WIFI:  SettingsWifi::run(key, lcd);  break;
            default: break;
        }
        // clang-format on
    }

    void handleMenuNavigation(InputAction action)
    {
        // clang-format off
        if (action == ACT_NONE) return;

        switch (action)
        {
        case ACT_LEFT:
            model.currentIndex = (model.currentIndex - 1 + model.totalApps) % model.totalApps;
            MenuView::draw(lcd, model.currentIndex, model.totalApps, model.appNames);
            break;

        case ACT_RIGHT:
            model.currentIndex = (model.currentIndex + 1) % model.totalApps;
            MenuView::draw(lcd, model.currentIndex, model.totalApps, model.appNames);
            break;

        case ACT_CONFIRM:
        case ACT_SELECT:
            currentSystemState = (SystemState)(model.currentIndex + 1);
            lcd.clear();
            if (currentSystemState == APP_WEATHER) WeatherApp::init(lcd);
            if (currentSystemState == SETTINGS_WIFI) SettingsWifi::init(lcd);
            break;

        default: break;
        }
        // clang-format on
    }
}