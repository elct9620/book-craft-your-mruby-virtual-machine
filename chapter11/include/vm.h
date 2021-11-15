#ifndef MVM_VM_H
#define MVM_VM_H

#include "irep.h"
#include "value.h"

#define CASE(insn,ops) case insn: FETCH_##ops ();;
#define NEXT break

#ifdef __cplusplus
extern "C" {
#endif

mrb_value mrb_exec(const uint8_t* irep);

#ifdef __cplusplus
}
#endif


#endif
