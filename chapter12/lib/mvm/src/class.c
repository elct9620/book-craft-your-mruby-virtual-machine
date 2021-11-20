#include<mvm.h>

void mrb_define_method(const char* name, mrb_func_t func, struct kh_mt_s *methods) {
  int ret;
  khiter_t key = kh_put(mt, methods, name, &ret);
  kh_value(methods, key) = func;
}
