#include "UIActor.h"
#include "WiFiApp.h"
#include "ClockApp.h"
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);
static QueueHandle_t _uiQueue;

enum UIState
{
    IN_MENU,
    IN_APP
};
UIState currentState = IN_MENU;

IApp *activeApp = nullptr;
WiFiApp *wifiApp = nullptr;
ClockApp *clockApp = nullptr;

int currentSelection = 0;
const char *menuOptions[] = {"WiFi Config", "GPU Terminal", "Clock"};

void drawStatusBar()
{
    display.setTextSize(1);
    display.setTextColor(1);
    display.setCursor(100, 0);

    // clang-format off
    if (WiFi.status() == WL_CONNECTED) { display.print("W:ON"); }
    else { display.print("W:--"); }
    // clang-format on
}

void drawMenu()
{
    display.setCursor(0, 0);
    display.println("MINI-PC OS");
    display.drawLine(0, 10, 128, 10, 1);

    for (int i = 0; i < 3; i++)
    {
        display.setCursor(10, 18 + (i * 12));

        if (i == currentSelection)
            display.print("> ");
        else
            display.print("  ");

        display.println(menuOptions[i]);
    }
}

void uiTask(void *pvParameters)
{

    SystemMessage msg;

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println("OLED not found!");
        vTaskDelete(NULL);
    }

    display.clearDisplay();
    display.display();

    wifiApp = new WiFiApp(&display);
    clockApp = new ClockApp(&display);

    for (;;)
    {

        if (xQueueReceive(_uiQueue, &msg, pdMS_TO_TICKS(10)))
        {

            if (msg.type != MSG_KEY_EVENT)
                goto render;

            if (msg.key == 'q')
            {
                currentState = IN_MENU;
                activeApp = nullptr;
                goto render;
            }

            if (currentState == IN_APP && activeApp != nullptr)
            {
                activeApp->onKeyEvent(msg.key);
                goto render;
            }

            if (currentState == IN_MENU)
            {
                if (msg.key == 'w')
                    currentSelection = (currentSelection - 1 + 3) % 3;
                if (msg.key == 's')
                    currentSelection = (currentSelection + 1) % 3;
                if (msg.key == 'e')
                {
                    if (currentSelection == 0)
                    {
                        currentState = IN_APP;
                        activeApp = wifiApp;
                        activeApp->onEnter();
                    }

                    if (currentSelection == 2)
                    {
                        currentState = IN_APP;
                        activeApp = clockApp;
                        activeApp->onEnter();
                    }
                }
            }
        }

    render:
        display.clearDisplay();

        // clang-format off
        if (currentState == IN_MENU) { drawMenu(); }
        else if (activeApp != nullptr) { activeApp->draw(); }
        // clang-format on

        drawStatusBar();
        display.display();

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void startUIActor(QueueHandle_t queue)
{
    _uiQueue = queue;
    xTaskCreatePinnedToCore(uiTask, "UIActor", 4096, NULL, 1, NULL, 1);
}