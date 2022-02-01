#ifndef MVM_VALUE_H
#define MVM_VALUE_H

#include<stdlib.h>
#include<string.h>

enum mrb_vtype {
  MRB_TYPE_FALSE = 0,
  MRB_TYPE_TRUE,
  MRB_TYPE_FIXNUM,
  MRB_TYPE_STRING,
  MRB_TYPE_PROC,
  MRB_TYPE_CLASS,
};

typedef struct mrb_value {
  union {
    void *p;
    int i;
  } value;
  enum mrb_vtype type;
} mrb_value;


#define SET_VALUE(o, ttt, attr, v) do {\
  (o).type = ttt;\
  (o).attr = v;\
} while(0)

#define SET_NIL_VALUE(r) SET_VALUE(r, MRB_TYPE_FALSE, value.i, 0)
#define SET_FALSE_VALUE(r) SET_VALUE(r, MRB_TYPE_FALSE, value.i, 1)
#define SET_TRUE_VALUE(r) SET_VALUE(r, MRB_TYPE_TRUE, value.i, 1)
#define SET_INT_VALUE(r, n) SET_VALUE(r, MRB_TYPE_FIXNUM, value.i, (n))
#define SET_CLASS_VALUE(r, c) SET_VALUE(r, MRB_TYPE_CLASS, value.p, (c))

#define IS_FALSE_VALUE(r) (r.type == MRB_TYPE_FALSE)
#define IS_CLASS_VALUE(r) (r.type == MRB_TYPE_CLASS)
#define IS_STRING_VALUE(r) (r.type == MRB_TYPE_STRING)

#define mrb_fixnum(o) (o).value.i
#define mrb_int(o) mrb_fixnum(o)

static inline mrb_value mrb_nil_value(void) {
  mrb_value v;
  SET_NIL_VALUE(v);
  return v;
}

static inline mrb_value mrb_fixnum_value(int i) {
  mrb_value v;
  SET_INT_VALUE(v, i);
  return v;
}

static inline mrb_value mrb_str_new(const uint8_t* p, int len) {
  mrb_value v;

  char* str = (char*)malloc(len + 1);
  memcpy(str, p, len);

  v.type = MRB_TYPE_STRING;
  v.value.p = (void*)str;

  return v;
}
#endif
