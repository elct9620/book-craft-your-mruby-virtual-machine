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

extern void mrb_define_method(RClass* klass, const char* name, mrb_func_t func);
RClass* mrb_alloc_class(RClass* super);

#ifdef __cplusplus
}
#endif

#endif
