#ifndef APP_H_
#define APP_H_

#include<mvm.h>

mrb_value mrb_point_initialize(mrb_state* mrb, mrb_value self);
mrb_value mrb_point_get_x(mrb_state* mrb, mrb_value self);
mrb_value mrb_point_set_x(mrb_state* mrb, mrb_value self);
mrb_value mrb_point_to_string(mrb_state* mrb, mrb_value self);

mrb_value mrb_sleep(mrb_state* mrb, mrb_value self);

void initialize_app(mrb_state* mrb);

#endif
