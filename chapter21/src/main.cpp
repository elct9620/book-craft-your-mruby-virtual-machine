#include<app.h>
#include<mrb.h>

static mrb_state* mrb;

#ifdef DEBUG
#ifndef UNIT_TEST
int main(int argc, char** argv) {
  mrb = mrb_open();
  initialize_app(mrb);

  mrb_exec(mrb, bin + 34);
  mrb_close(mrb);
}
#endif
#else
#include <Arduino.h>

void setup() {
  Serial.begin(9600);

  mrb = mrb_open();
  initialize_app(mrb);
}

void loop() {
  mrb_exec(mrb, bin + 34);
  delay(500);
}
#endif
