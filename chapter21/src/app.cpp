#include<stdio.h>
#include "app.h"
#include "hal.h"

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

mrb_value mrb_sleep(mrb_state* mrb, mrb_value self) {
  hal_delay(mrb_fixnum(mrb->ci->argv[0]));
  return self;
}

void initialize_app(mrb_state* mrb) {
  mrb_define_method(mrb->object_class, "sleep", mrb_sleep);

  RClass* point = mrb_define_class(mrb, "Point", mrb->object_class);
  mrb_define_method(point, "initialize", point_initialize);
  mrb_define_method(point, "x", point_get_x);
  mrb_define_method(point, "x=", point_set_x);
  mrb_define_method(point, "to_s", point_to_string);
}
