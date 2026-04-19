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
        AppInitFn initFn;
        AppRunFn runFn;
    };

    // clang-format off
    static const AppRecord APPS[] = {
        {APP_WEATHER,   "WEATHER", icon_weather, WeatherApp::init,   WeatherApp::run},
        {APP_DINO,      "DINO",    icon_dino,    DinoApp::init,      DinoApp::run},
        {SETTINGS_WIFI, "WIFI",    icon_wifi,    SettingsWifi::init, SettingsWifi::run},
    };
    const int TOTAL_APPS = sizeof(APPS) / sizeof(APPS[0]);
    // clang-format on

    struct ModelMenu
    {
        int index = 0;
        SystemState state = STATE_MENU;
        char ssid[33] = "";
        char pass[65] = "";
    };
    static ModelMenu modelMenu;

    const char *getSSID() { return modelMenu.ssid; }
    const char *getWifiPass() { return modelMenu.pass; }

    void setSSID(const char *newSsid)
    {
        strncpy(modelMenu.ssid, newSsid, 32);
        modelMenu.ssid[32] = '\0';
    }

    void setWifiPass(const char *newPass)
    {
        strncpy(modelMenu.pass, newPass, 64);
        modelMenu.pass[64] = '\0';
    }

    LiquidCrystal_I2C lcd(0x27, 16, 2);

    void handleMenuNavigation(InputAction action);

    void loadMenuIcons()
    {
        for (int i = 0; i < TOTAL_APPS; i++)
            lcd.createChar(i, (uint8_t *)APPS[i].iconData);
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
        if (modelMenu.state == STATE_MENU) { handleMenuNavigation(action);} 
        else {
            if (APPS[modelMenu.index].runFn) 
                APPS[modelMenu.index].runFn(key, lcd);
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
            if (APPS[modelMenu.index].initFn) {
                APPS[modelMenu.index].initFn(lcd);
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