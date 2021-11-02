#ifndef MVM_VALUE_H
#define MVM_VALUE_H

enum mrb_vtype {
  MRB_TYPE_FALSE = 0,
  MRB_TYPE_TRUE,
  MRB_TYPE_FIXNUM,
};

typedef struct mrb_value {
  union {
    int i;
  } value;
  enum mrb_vtype type;
} mrb_value;

static inline mrb_value mrb_fixnum_value(int i) {
  mrb_value v;
  v.type = MRB_TYPE_FIXNUM;
  v.value.i = i;
  return v;
}

#endif
