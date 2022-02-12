#if defined(ARDUINO)

#include<Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include "hal.h"

TFT_eSPI tft = TFT_eSPI();

void hal_delay(int millisecond) {
  delay(millisecond);
}

void hal_screen_init() {
  tft.init();
  tft.setTextSize(1);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
}

void hal_screen_clear() {
  tft.fillScreen(TFT_BLACK);
}

void hal_screen_print(const char* text, int x, int y) {
  tft.drawString(text, x, y, 1);
}

#endif
