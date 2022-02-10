#include<mvm.h>
#include<tgc.h>

mrb_value mrb_str_new(mrb_state* mrb, const uint8_t* p, int len) {
  mrb_value v;

  char* str = (char*)tgc_alloc(&mrb->gc, len + 1);
  memcpy(str, p, len);

  v.type = MRB_TYPE_STRING;
  v.value.p = (void*)str;

  return v;
}

mrb_value mrb_str_value(mrb_state* mrb, const char* str) {
  return mrb_str_new(mrb, (const uint8_t*)str, strlen(str) + 1);
}
