#ifndef TACHOMETER_H
#define TACHOMETER_H

#include <Arduino.h>

extern volatile unsigned long pulseCount;
extern volatile unsigned long lastPulseTime;
extern volatile float rpm;
extern unsigned short roundedRPM;

void setupTachometer();
void loopTachometer();
void handleDisplayMode();
void processRPMData();
void updateSerialDisplay();
void IRAM_ATTR detectPulse();

#endif