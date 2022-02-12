#ifndef APP_H_
#define APP_H_

#include<mvm.h>

mrb_value point_initialize(mrb_state* mrb, mrb_value self);
mrb_value point_get_x(mrb_state* mrb, mrb_value self);
mrb_value point_set_x(mrb_state* mrb, mrb_value self);
mrb_value point_to_string(mrb_state* mrb, mrb_value self);

mrb_value screen_init(mrb_state* mrb, mrb_value self);
mrb_value screen_clear(mrb_state* mrb, mrb_value self);
mrb_value screen_print(mrb_state* mrb, mrb_value self);

mrb_value mrb_sleep(mrb_state* mrb, mrb_value self);

void initialize_app(mrb_state* mrb);

#endif
