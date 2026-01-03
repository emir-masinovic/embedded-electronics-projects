#include "SettingsWifiView.h"
#include "utils.h"

namespace SettingsWifiView
{
    void draw(LiquidCrystal_I2C &lcd, const SettingsWifi::WifiDisplayData &data)
    {
        if (data.activeRow < 2)
        {
            int globalPage = data.cursorX / 13;
            for (int r = 0; r < 2; r++)
            {
                lcd.setCursor(0, r);
                lcd.print(r == 0 ? "W:" : "P:");

                const char *buf = (r == 0) ? data.ssid : data.pass;

                for (int i = 0; i < 13; i++)
                {
                    int pos = (globalPage * 13) + i;
                    if (r == data.activeRow && pos == data.cursorX)
                    {
                        if (millis() % 600 < 300)
                            lcd.print(Utils::charsets[data.inputMode][data.charIdx]);
                        else
                            lcd.print((char)255);
                    }
                    else if (pos < (int)strlen(buf))
                    {
                        lcd.print((r == 1 && data.privacyMode) ? '*' : buf[pos]);
                    }
                    else
                        lcd.print(" ");
                }
                lcd.setCursor(14, r);
                lcd.print("|");
                lcd.print(globalPage + 1);
            }
        }
        else
        {
            lcd.setCursor(0, 0);

            if (data.totalActive == 0)
            {
                lcd.print("Saved: 0/0      ");
            }
            else
            {
                lcd.print("Slot: ");
                lcd.print(data.savedIdx + 1);
                lcd.print("/");
                lcd.print(data.totalActive);
                lcd.print("     "); // Clear trailing chars
            }

            lcd.setCursor(0, 1);
            if (data.currentProfileActive)
            {
                String s = String(data.carouselSsid);
                lcd.print("< ");
                lcd.print(s.length() > 12 ? s.substring(0, 12) : s);
                // Fill remaining space with spaces to clear old text
                for (int i = 0; i < (13 - (int)s.length()); i++)
                    lcd.print(" ");
                lcd.setCursor(15, 1);
                lcd.print(">");
            }
            else
            {
                lcd.print("<    Empty     >");
            }
        }
    }

    void drawMessage(LiquidCrystal_I2C &lcd, const char *line1, const char *line2)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(line1);
        lcd.setCursor(0, 1);
        lcd.print(line2);
    }
}