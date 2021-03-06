#include<mvm.h>
#include<stdio.h>

#include <stdint.h>
#if defined __GNUC__
__attribute__((aligned(4)))
#elif defined _MSC_VER
__declspec(align(4))
#endif

const uint8_t bin[] = {
  /**
   * i = 0
   * while i < 100
   *   point = Point.new(1, i)
   *   puts point.to_s
   *   i += 1
   * end
   */
  0x52,0x49,0x54,0x45,0x30,0x30,0x30,0x37,0x70,0x20,0x00,0x00,0x00,0xb5,0x4d,0x41,
  0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x00,0x79,0x30,0x30,
  0x30,0x32,0x00,0x00,0x01,0x22,0x00,0x03,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x3b,
  0x06,0x01,0x21,0x00,0x2a,0x1b,0x03,0x00,0x07,0x04,0x01,0x05,0x01,0x2e,0x03,0x01,
  0x02,0x01,0x02,0x03,0x10,0x03,0x01,0x04,0x02,0x2e,0x04,0x02,0x00,0x2e,0x03,0x03,
  0x01,0x01,0x03,0x01,0x3c,0x03,0x01,0x01,0x01,0x03,0x01,0x03,0x01,0x03,0x04,0x64,
  0x42,0x03,0x22,0x03,0x00,0x05,0x0f,0x03,0x37,0x03,0x67,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x04,0x00,0x05,0x50,0x6f,0x69,0x6e,0x74,0x00,0x00,0x03,0x6e,0x65,0x77,
  0x00,0x00,0x04,0x74,0x6f,0x5f,0x73,0x00,0x00,0x04,0x70,0x75,0x74,0x73,0x00,0x4c,
  0x56,0x41,0x52,0x00,0x00,0x00,0x1e,0x00,0x00,0x00,0x02,0x00,0x01,0x69,0x00,0x05,
  0x70,0x6f,0x69,0x6e,0x74,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x02,0x45,0x4e,0x44,
  0x00,0x00,0x00,0x00,0x08,
};

static mrb_state* mrb;

mrb_value point_initialize(mrb_state* mrb, mrb_value self) {
  mrb_iv_set(self, "@x", mrb->ci->argv[0]);
  mrb_iv_set(self, "@y", mrb->ci->argv[1]);

  return self;
}

mrb_value point_get_x(mrb_state* mrb, mrb_value self) {
  return mrb_iv_get(self, "@x");
}

mrb_value point_set_x(mrb_state* mrb, mrb_value self) {
  return mrb_iv_set(self, "@x", mrb->ci->argv[0]);
}

mrb_value point_to_string(mrb_state* mrb, mrb_value self) {
  char buffer[128];
  mrb_value x = mrb_iv_get(self, "@x");
  mrb_value y = mrb_iv_get(self, "@y");

  sprintf(buffer, "#<Point x=%d, y=%d>", mrb_fixnum(x), mrb_fixnum(y));
  return mrb_str_value(mrb, buffer);
}

#ifdef DEBUG
#ifndef UNIT_TEST
int main(int argc, char** argv) {
  mrb = mrb_open();

  RClass* point = mrb_define_class(mrb, "Point", mrb->object_class);
  mrb_define_method(point, "initialize", point_initialize);
  mrb_define_method(point, "x", point_get_x);
  mrb_define_method(point, "x=", point_set_x);
  mrb_define_method(point, "to_s", point_to_string);

  mrb_exec(mrb, bin + 34);
  mrb_close(mrb);
}
#endif
#else
#include <Arduino.h>

void setup() {
  Serial.begin(9600);

  mrb = mrb_open();
}

void loop() {
  mrb_exec(mrb, bin + 34);
  delay(5000);
}
#endif
