#ifndef HAL_H_
#define HAL_H_

void hal_delay(int millisecond);
void hal_screen_init();
void hal_screen_clear();
void hal_screen_print(const char* text, int x, int y);

#endif
