#if !defined(ARDUINO)

#include "hal.h"
#include "stdio.h"

void hal_delay(int millisecond) {
  // NOOP
}

void hal_screen_init() {
  // NOOP
}

void hal_screen_clear() {
  // NOOP
}

void hal_screen_print(const char* text, int x, int y) {
  printf("[%d, %d] %s\n", x, y, text);
}

#endif
