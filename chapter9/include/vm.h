#ifndef MVM_VM_H
#define MVM_VM_H

#include "irep.h"
#include "value.h"

#define CASE(insn,ops) case insn: FETCH_##ops ();;
#define NEXT break

mrb_value mrb_exec(const uint8_t* irep);

#endif
