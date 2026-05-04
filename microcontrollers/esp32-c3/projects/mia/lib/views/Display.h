#ifndef DISPLAY_H
#define DISPLAY_H

#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include "../models/Manager.h"

class Display
{
private:
    GxEPD2_BW<GxEPD2_290_T94, GxEPD2_290_T94::HEIGHT> display;

public:
    int offX = 0;
    int offY = 0;
    int rot = 1;

    Display();
    void init();

    void clear();
    void drawShape(int x, int y, int w, int h, bool isCircle);
    void printRaw(int x, int y, String msg, bool partial);
    void drawText(int x, int y, String msg);
    void drawRect(int x, int y, int w, int h);
    void drawFastLine(int y);
    void render();
    void update();
    void drawClock(const char *timeStr);
};

#endif