#ifndef MVM_CLASS_H
#define MVM_CLASS_H

#include<khash.h>

#include "mvm/vm.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef mrb_value (*mrb_func_t)(mrb_state* mrb);

KHASH_MAP_INIT_STR(mt, mrb_func_t)

extern void mrb_define_method(mrb_state* mrb, const char* name, mrb_func_t func);

#ifdef __cplusplus
}
#endif

#endif
