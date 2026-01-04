#include "MenuManager.h"
#include "MenuView.h"
#include "keypad_config.h"
#include "apps.h"
#include "icons.h"
#include "WeatherApp.h"
#include "SettingsWifi.h"
#include "utils.h"
#include "DinoApp.h"

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

    struct AppRecord
    {
        SystemState state;
        const char *name;
        const uint8_t *iconData;
    };

    static const AppRecord APPS[] = {
        {APP_WEATHER, "WEATHER", icon_weather},
        {APP_DINO, "DINO", icon_dino},
        {APP_CONSOLE, "CONSOLE", icon_console},
        {SETTINGS_WIFI, "WIFI", icon_wifi},
    };
    const int TOTAL_APPS = sizeof(APPS) / sizeof(APPS[0]);

    struct ModelMenu
    {
        int index = 0;
        SystemState state = STATE_MENU;
        char ssid[33] = "";
        char pass[65] = "";
    };
    static ModelMenu modelMenu;

    const char *getSSID() { return modelMenu.ssid; }
    void setSSID(const char *s)
    {
        strncpy(modelMenu.ssid, s, 32);
        modelMenu.ssid[32] = '\0';
    }

    const char *getWifiPass() { return modelMenu.pass; }
    void setWifiPass(const char *s)
    {
        strncpy(modelMenu.pass, s, 64);
        modelMenu.pass[64] = '\0';
    }

    LiquidCrystal_I2C lcd(0x27, 16, 2);

    void handleMenuNavigation(InputAction action);

    void loadMenuIcons()
    {
        for (int i = 0; i < TOTAL_APPS; i++)
        {
            lcd.createChar(i, (uint8_t *)APPS[i].iconData);
        }
    }

    void processEvents(char key)
    {
        InputAction action = getAction(key);

        // Global Action: Exit always takes priority
        if (action == ACT_BACK && modelMenu.state != STATE_MENU)
        {
            modelMenu.state = STATE_MENU;
            MenuView::draw(lcd, modelMenu.index, TOTAL_APPS, APPS[modelMenu.index].name);
            return;
        }

        // clang-format off
        switch (modelMenu.state) {
            case STATE_MENU:     handleMenuNavigation(action); break;
            case APP_WEATHER:    WeatherApp::run(key, lcd);    break;
            case SETTINGS_WIFI:  SettingsWifi::run(key, lcd);  break;
            default: break;
        }
        // clang-format on
    }

    // clang-format off
   void handleMenuNavigation(InputAction action) {
        if (action == ACT_NONE) return;

        if (action == ACT_LEFT)  modelMenu.index = (modelMenu.index - 1 + TOTAL_APPS) % TOTAL_APPS;
        if (action == ACT_RIGHT) modelMenu.index = (modelMenu.index + 1) % TOTAL_APPS;

        if (action == ACT_LEFT || action == ACT_RIGHT) {
            MenuView::draw(lcd, modelMenu.index, TOTAL_APPS, APPS[modelMenu.index].name);
        }

        if (action == ACT_SELECT || action == ACT_CONFIRM) {
            modelMenu.state = APPS[modelMenu.index].state;
            
            switch (modelMenu.state) {
                case APP_WEATHER:   WeatherApp::init(lcd); break;
                case APP_DINO:      DinoApp::init(lcd);    break;
                case SETTINGS_WIFI: SettingsWifi::init(lcd); break;
                default: break;
            }
        }
    }
    // clang-format on

    void init()
    {
        lcd.init();
        lcd.backlight();
        loadMenuIcons();
        MenuView::draw(lcd, modelMenu.index, TOTAL_APPS, APPS[modelMenu.index].name);
    }

    void run() { processEvents(keypad.getKey()); }
}