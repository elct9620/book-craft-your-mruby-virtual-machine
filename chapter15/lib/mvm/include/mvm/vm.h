#ifndef MVM_VM_H
#define MVM_VM_H

#include "mvm/irep.h"
#include "mvm/value.h"

#define CASE(insn,ops) case insn: FETCH_##ops ();;
#define NEXT break

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mrb_callinfo {
  int argc;
  mrb_value* argv;
} mrb_callinfo;

typedef struct mrb_state {
  struct kh_mt_s *mt;

  int exc;
  mrb_callinfo* ci;
} mrb_state;

extern mrb_state* mrb_open();
extern void mrb_close(mrb_state* mrb);

mrb_value mrb_exec(mrb_state* mrb, const uint8_t* irep);

#ifdef __cplusplus
}
#endif


#endif
