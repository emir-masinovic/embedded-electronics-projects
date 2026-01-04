#include "DinoApp.h"
#include "icons.h"

namespace DinoApp
{
    enum EnumsDino
    {
        ICON_DINO = 7,
        ICON_CACTUS = 1,
    };

    void init(LiquidCrystal_I2C &lcd)
    {
        lcd.clear();
        lcd.createChar(ICON_DINO, (uint8_t *)icon_cactus);
        lcd.createChar(ICON_CACTUS, (uint8_t *)icon_cactus);

        lcd.setCursor(0, 1);
        lcd.write(ICON_DINO);
        lcd.setCursor(15, 1);
        lcd.write(ICON_CACTUS);
    }

    void run(char key, LiquidCrystal_I2C &lcd)
    {
    }

}
