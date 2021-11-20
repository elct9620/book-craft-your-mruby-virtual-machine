#ifndef MVM_CLASS_H
#define MVM_CLASS_H

#include<khash.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef mrb_value (*mrb_func_t)();

KHASH_MAP_INIT_STR(mt, mrb_func_t)

extern void mrb_define_method(const char* name, mrb_func_t func, struct kh_mt_s *methods);

#ifdef __cplusplus
}
#endif

#endif
