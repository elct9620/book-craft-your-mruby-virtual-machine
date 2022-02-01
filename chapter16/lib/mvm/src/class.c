#include<mvm.h>

void mrb_define_method(RClass* klass, const char* name, mrb_func_t func) {
  int ret;
  khiter_t key = kh_put(mt, klass->mt, name, &ret);
  kh_value(klass->mt, key) = func;
}

RClass* mrb_alloc_class(RClass* super) {
  RClass* klass = (RClass*)malloc(sizeof(RClass));
  klass->super = super;
  klass->mt = kh_init(mt);

  return klass;
}

RClass* mrb_define_class(mrb_state* mrb, const char* name, RClass* super) {
  int ret;
  RClass* klass = mrb_alloc_class(super);

  khiter_t key = kh_put(ct, mrb->ct, name, &ret);
  kh_value(mrb->ct, key) = klass;

  return klass;
}
