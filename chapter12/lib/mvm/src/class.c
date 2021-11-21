#include<mvm.h>

void mrb_define_method(mrb_state* mrb, const char* name, mrb_func_t func) {
  int ret;
  khiter_t key = kh_put(mt, mrb->mt, name, &ret);
  kh_value(mrb->mt, key) = func;
}
