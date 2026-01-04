#include "SettingsWifi.h"
#include "SettingsWifiView.h"
#include "MenuManager.h"
#include "utils.h"
#include <EEPROM.h>

#ifdef CLOSED
#undef CLOSED
#endif

#ifdef LISTEN
#undef LISTEN
#endif

#include <ESP8266WiFi.h>
#include "keypad_config.h"

namespace SettingsWifi
{
    using namespace Utils;

    struct NetworkProfile
    {
        char ssid[33];
        char pass[65];
        bool active;
    };

    struct WifiModel
    {
        char tempSsid[33] = "";
        char tempPass[65] = "";
        int cursorX = 0;
        int activeRow = 0; // 0: SSID, 1: Pass, 2: Carousel
        int inputMode = 0;
        int selectedCharIndex = 0;
        bool privacyMode = false;
        int savedIdx = 0;
        int sessionWriteCount = 0;
        unsigned long actionTimer = 0;
    };

    static WifiModel model;
    static const int MAX_PROFILES = 5;
    static NetworkProfile profiles[MAX_PROFILES];

    void handleContinuousKeys(InputAction action, KeyState holdKeyState, char *buffer);
    void attemptConnection(LiquidCrystal_I2C &lcd);
    void loadAllFromEEPROM();
    void saveCurrentToSlot();
    void commitWithSafety(int slot);
    char *getActiveBuffer();
    void snapCursor();
    void deleteCharAtCursor(char *buf);
    int getActiveCount();

    void init(LiquidCrystal_I2C &lcd)
    {
        loadAllFromEEPROM();
        lcd.clear();
    }

    void run(char key, LiquidCrystal_I2C &lcd)
    {
        char *buf = getActiveBuffer();
        InputAction action = getAction(key);
        KeyState holdState = keypad.key[0].kstate;
        InputAction holdAct = getAction(keypad.key[0].kchar);

        handleContinuousKeys(holdAct, holdState, buf);

        // Handle vertical navigation
        if (navigate(action, model.activeRow, 3))
        {
            snapCursor();
            lcd.clear();
        }

        // clang-format off
        switch (action) {
            case ACT_HOME:    model.cursorX = 0; break;
            case ACT_END:     model.cursorX = (int)strlen(buf); break;
            case ACT_CONFIRM: if (model.activeRow < 2) attemptConnection(lcd); break;
            case ACT_LEFT:
                if (model.activeRow < 2) moveClamped(model.cursorX, -1, 0, (int)strlen(buf));
                else model.savedIdx = wrapValue(model.savedIdx, -1, MAX_PROFILES);
                break;

            case ACT_RIGHT:
                if (model.activeRow < 2) moveClamped(model.cursorX, 1, 0, (int)strlen(buf));
                else model.savedIdx = wrapValue(model.savedIdx, 1, MAX_PROFILES);
                break;

            case ACT_SELECT:
                    // View 1: Typing characters in the editor
                    if (model.activeRow < 2) {
                        int limit = (model.activeRow == 0) ? 31 : 63;
                        if (model.cursorX < limit) {
                            buf[model.cursorX] = charsets[model.inputMode][model.selectedCharIndex];
                            if (model.cursorX == (int)strlen(buf)) buf[model.cursorX + 1] = '\0';
                            model.cursorX++;
                        }
                        break;
                    } 
                    
                    // View 2: Loading a profile from the Carousel
                    if (profiles[model.savedIdx].active) {
                        strncpy(model.tempSsid, profiles[model.savedIdx].ssid, 33);
                        strncpy(model.tempPass, profiles[model.savedIdx].pass, 65);
                        model.activeRow = 0;
                        model.cursorX = (int)strlen(model.tempSsid);
                        lcd.clear();
                    }
                break;

            case ACT_DELETE:
                if (model.activeRow < 2) deleteChar(buf, model.cursorX);
                else {
                    profiles[model.savedIdx].active = false;
                    commitWithSafety(model.savedIdx);
                }
                break;

            case ACT_ALT:
                if (key == '*') {
                    model.inputMode = wrapValue(model.inputMode, 1, 4);
                    model.selectedCharIndex = 0;
                } else { model.privacyMode = !model.privacyMode; }
                break;

            default:
                int setLen = strlen(charsets[model.inputMode]);
                if (key == '1') model.selectedCharIndex = wrapValue(model.selectedCharIndex, -1, setLen);
                if (key == '3') model.selectedCharIndex = wrapValue(model.selectedCharIndex, 1, setLen);
                break;
        }
        // clang-format on

        const char *cSSID = profiles[model.savedIdx].active ? profiles[model.savedIdx].ssid : "Empty";
        WifiDisplayData data = {
            model.tempSsid, model.tempPass, model.cursorX, model.activeRow,
            model.inputMode, model.selectedCharIndex, model.privacyMode,
            model.savedIdx, getActiveCount(), profiles[model.savedIdx].active, cSSID};
        SettingsWifiView::draw(lcd, data);
    }

    void attemptConnection(LiquidCrystal_I2C &lcd)
    {
        if (strlen(model.tempSsid) < 2 || strlen(model.tempPass) < 8)
        {
            SettingsWifiView::drawMessage(lcd, "ERR: TOO SHORT", "MIN: 2 SSID/8 PS");
            delay(2500);
            return;
        }

        SettingsWifiView::drawMessage(lcd, "Connecting to:", model.tempSsid);
        WiFi.disconnect(true);
        WiFi.begin(model.tempSsid, model.tempPass);

        int retry = 0;
        const char throb[] = {'|', '/', '-', '\\'};
        while (WiFi.status() != WL_CONNECTED && retry < 30)
        {
            lcd.setCursor(15, 0);
            lcd.print(throb[retry % 4]);
            delay(500);
            retry++;
        }

        if (WiFi.status() == WL_CONNECTED)
        {
            SettingsWifiView::drawMessage(lcd, "CONNECTED!", model.tempSsid);
            saveCurrentToSlot();
            MenuManager::setSSID(model.tempSsid);
            MenuManager::setWifiPass(model.tempPass);
        }
        else
        {
            SettingsWifiView::drawMessage(lcd, "FAILED", "CHECK CREDENTIALS");
        }
        delay(3000);
        lcd.clear();
    }

    char *getActiveBuffer() { return (model.activeRow == 0) ? model.tempSsid : model.tempPass; }

    void snapCursor()
    {
        int len = strlen(getActiveBuffer());
        if (model.cursorX > len)
            model.cursorX = len;
    }

    void deleteCharAtCursor(char *buf)
    {
        int strLen = strlen(buf);
        if (strLen > 0 && model.cursorX > 0)
        {
            for (int i = model.cursorX - 1; i < strLen; i++)
                buf[i] = buf[i + 1];
            model.cursorX--;
        }
    }

    // clang-format off
    void handleContinuousKeys(InputAction action, KeyState holdKeyState, char *buffer) {
        if (model.activeRow >= 2 || !shouldRepeat(holdKeyState, model.actionTimer)) { return; }
        switch (action) {
            case ACT_DELETE: deleteChar(buffer, model.cursorX); break;
            case ACT_LEFT:   moveClamped(model.cursorX, -1, 0, (int)strlen(buffer)); break;
            case ACT_RIGHT:  moveClamped(model.cursorX,  1, 0, (int)strlen(buffer)); break;
            default: break;
        }
    }
    // clang-format on

    int getActiveCount()
    {
        int count = 0;
        for (int i = 0; i < MAX_PROFILES; i++)
            if (profiles[i].active)
                count++;
        return count;
    }

    void loadAllFromEEPROM()
    {
        EEPROM.begin(512);
        for (int i = 0; i < MAX_PROFILES; i++)
            EEPROM.get(i * sizeof(NetworkProfile), profiles[i]);
    }

    void commitWithSafety(int slot)
    {
        if (model.sessionWriteCount >= 10)
            return;

        NetworkProfile existing;

        EEPROM.get(slot * sizeof(NetworkProfile), existing);

        if (memcmp(&existing, &profiles[slot], sizeof(NetworkProfile)) == 0)
            return;

        EEPROM.put(slot * sizeof(NetworkProfile), profiles[slot]);

        if (EEPROM.commit())
            model.sessionWriteCount++;
    }

    void saveCurrentToSlot()
    {
        int slot = -1;
        for (int i = 0; i < MAX_PROFILES; i++)
        {
            if (profiles[i].active && strcmp(profiles[i].ssid, model.tempSsid) == 0)
            {
                slot = i;
                break;
            }
        }
        if (slot == -1)
        {
            for (int i = 0; i < MAX_PROFILES; i++)
            {
                if (!profiles[i].active)
                {
                    slot = i;
                    break;
                }
            }
        }
        if (slot == -1)
            slot = model.savedIdx;
        profiles[slot].active = true;
        strncpy(profiles[slot].ssid, model.tempSsid, 33);
        strncpy(profiles[slot].pass, model.tempPass, 65);
        commitWithSafety(slot);
    }
}