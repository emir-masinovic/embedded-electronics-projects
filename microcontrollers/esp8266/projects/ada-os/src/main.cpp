#include <Arduino.h>
#include "controllers/MenuManager.h"

MenuManager menuManager;

void setup() { menuManager.setup(); }

void loop() { menuManager.loop(); }