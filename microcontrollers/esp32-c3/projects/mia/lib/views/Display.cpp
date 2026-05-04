#include "Display.h"

Display::Display() : display(GxEPD2_290_T94(7, 2, 3, 5)) {}

void Display::init()
{
    SPI.begin(4, -1, 6, 7);
    display.init(115200, true, 2, false);

    display.setRotation(rot);
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setTextWrap(false);

    Serial.println("--- DISPLAY DEBUG ---");
    Serial.print("Width: ");
    Serial.println(display.width());
    Serial.print("Height: ");
    Serial.println(display.height());
    Serial.print("Rotation: ");
    Serial.println(display.getRotation());
    Serial.println("---------------------");

    clear();
}

void Display::clear()
{
    display.setFullWindow();
    display.firstPage();
    do
    {
        display.fillScreen(GxEPD_WHITE);
    } while (display.nextPage());
}

void Display::drawShape(int x, int y, int w, int h, bool isCircle)
{
    display.setPartialWindow(0, 0, 296, 128);
    display.firstPage();
    do
    {
        display.fillScreen(GxEPD_WHITE);
        if (isCircle)
            display.drawCircle(x + offX, y + offY, w, GxEPD_BLACK);
        else
            display.drawRect(x + offX, y + offY, w, h, GxEPD_BLACK);
    } while (display.nextPage());
}

void Display::printRaw(int x, int y, String msg, bool partial)
{
    if (partial)
        display.setPartialWindow(0, 0, 296, 128);
    else
        display.setFullWindow();

    display.setRotation(rot);
    display.firstPage();
    do
    {
        if (!partial)
            display.fillScreen(GxEPD_WHITE);
        display.setCursor(x + offX, y + offY);
        display.print(msg);
    } while (display.nextPage());
}

void Display::drawText(int x, int y, String msg)
{
    display.setCursor(x + offX, y + offY);
    display.print(msg);
}

void Display::drawRect(int x, int y, int w, int h)
{
    display.drawRect(x + offX, y + offY, w, h, GxEPD_BLACK);
}

void Display::render()
{
    display.display();
}

void Display::drawClock(const char *timeStr)
{
    display.setPartialWindow(200, 0, 96, 40);
    display.firstPage();
    do
    {
        display.fillScreen(GxEPD_WHITE);
        drawFastLine(35);
        display.setCursor(200, 25);
        display.print(timeStr);
    } while (display.nextPage());
}

void Display::drawFastLine(int y)
{
    display.drawFastHLine(0, y, 296, GxEPD_BLACK);
}

void Display::update()
{
    display.display(true);
}