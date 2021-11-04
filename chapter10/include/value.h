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


#define SET_VALUE(o, ttt, attr, v) do {\
  (o).type = ttt;\
  (o).attr = v;\
} while(0)

#define SET_NIL_VALUE(r) SET_VALUE(r, MRB_TYPE_FALSE, value.i, 0)
#define SET_FALSE_VALUE(r) SET_VALUE(r, MRB_TYPE_FALSE, value.i, 1)
#define SET_TRUE_VALUE(r) SET_VALUE(r, MRB_TYPE_TRUE, value.i, 1)
#define SET_INT_VALUE(r, n) SET_VALUE(r, MRB_TYPE_FIXNUM, value.i, (n))

#define IS_FALSE_VALUE(r) (r.tt == MRB_TYPE_FALSE)

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

#endif
