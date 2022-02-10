#if defined(ARDUINO)

#include<Arduino.h>
#include "hal.h"

void hal_delay(int millisecond) {
  delay(millisecond);
}

#endif
