#include<mvm.h>
#include<stdio.h>

#include <stdint.h>
#if defined __GNUC__
__attribute__((aligned(4)))
#elif defined _MSC_VER
__declspec(align(4))
#endif

const uint8_t bin[] = {
  // puts App.run
  0x52,0x49,0x54,0x45,0x30,0x30,0x30,0x37,0x22,0x61,0x00,0x00,0x00,0x63,0x4d,0x41,
  0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x00,0x45,0x30,0x30,
  0x30,0x32,0x00,0x00,0x00,0x6d,0x00,0x01,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x10,
  0x10,0x01,0x1b,0x02,0x00,0x2e,0x02,0x01,0x00,0x2e,0x01,0x02,0x01,0x37,0x01,0x67,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x03,0x41,0x70,0x70,0x00,0x00,0x03,
  0x72,0x75,0x6e,0x00,0x00,0x04,0x70,0x75,0x74,0x73,0x00,0x45,0x4e,0x44,0x00,0x00,
  0x00,0x00,0x08,
};

mrb_value c_puts(mrb_state* mrb) {
  printf("argc: %d\n", mrb->ci->argc);
  printf("argv: %s\n", (char*)mrb->ci->argv->value.p);

  return mrb_nil_value();
}

mrb_value c_loop(mrb_state* mrb) {
  const uint8_t* irep = (const uint8_t*)mrb->ci->argv->value.p;

  mrb_value ret;
  while(mrb->exc == 0) {
    ret = mrb_exec(mrb, irep);
  }
  mrb->exc = 1;

  return ret;
}

mrb_value c_run(mrb_state* mrb) {
  const char* str = "Hello World";
  return mrb_str_new((const uint8_t*)str, 12);
}

static mrb_state* mrb;

#ifdef DEBUG
#ifndef UNIT_TEST
int main(int argc, char** argv) {
  mrb = mrb_open();
  mrb_define_method(mrb->object_class, "cputs", c_puts);
  mrb_define_method(mrb->object_class, "loop", c_loop);

  RClass* app = mrb_define_class(mrb, "App", mrb->object_class);
  mrb_define_method(app, "run", c_run);

  mrb_exec(mrb, bin + 34);
  mrb_close(mrb);
}
#endif
#else
#include <Arduino.h>

void setup() {
  Serial.begin(9600);

  mrb = mrb_open();
  mrb_define_method(mrb->object_class, "cputs");
}

void loop() {
  mrb_exec(mrb, bin + 34);
  delay(5000);
}
#endif
