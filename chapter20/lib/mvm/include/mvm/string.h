#ifndef MVM_STRING_H
#define MVM_STRING_H

#include<tgc.h>

#ifdef __cplusplus
extern "C" {
#endif

extern mrb_value mrb_str_new(mrb_state* mrb, const uint8_t* p, int len);
extern mrb_value mrb_str_value(mrb_state* mrb, const char* str);

#ifdef __cplusplus
}
#endif

#endif
