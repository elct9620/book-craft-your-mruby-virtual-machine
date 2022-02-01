#ifndef MVM_CLASS_H
#define MVM_CLASS_H

#include<khash.h>

#include "mvm/vm.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef mrb_value (*mrb_func_t)(mrb_state* mrb);

KHASH_MAP_INIT_STR(mt, mrb_func_t)
KHASH_MAP_INIT_STR(iv, mrb_value)

typedef struct RClass {
  struct kh_mt_s *mt;
  struct RClass *super;
} RClass;

typedef struct RObject {
  struct RClass* c;
  struct kh_iv_s *iv;
} RObject;

KHASH_MAP_INIT_STR(ct, RClass*)

extern void mrb_define_method(RClass* klass, const char* name, mrb_func_t func);
RClass* mrb_alloc_class(RClass* super);
RClass* mrb_define_class(mrb_state* mrb, const char* name, RClass* super);

static inline mrb_value mrb_class_value(RClass* klass) {
  mrb_value v;

  SET_CLASS_VALUE(v, klass);

  return v;
}

#ifdef __cplusplus
}
#endif

#endif
