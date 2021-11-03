#include<vm.h>
#include<opcode.h>

mrb_value mrb_exec(const uint8_t* bin) {
  const uint8_t* p = bin;
  uint8_t len;

  irep_header* irep = irep_read_header(p, &len);
  p += len;

  {
    p += 4; // Codelen
    size_t align = sizeof(uint32_t);
    p += -(intptr_t)p & (align - 1);
  }

  // Temp
  int32_t a = 0;
  int32_t b = 0;
  int32_t c = 0;
  mrb_value reg[irep->nregs];


  for(;;) {
    uint8_t insn = READ_B();

    switch(insn) {
      CASE(OP_NOP, Z) {
        NEXT;
      }
      CASE(OP_LOADI, BB) {
        SET_INT_VALUE(reg[a], b);
        NEXT;
      }
      CASE(OP_LOADINEG, BB) {
        SET_INT_VALUE(reg[a], b * -1);
        NEXT;
      }
      CASE(OP_LOADI__1, B) goto LOAD_I;
      CASE(OP_LOADI_0, B) goto LOAD_I;
      CASE(OP_LOADI_1, B) goto LOAD_I;
      CASE(OP_LOADI_2, B) goto LOAD_I;
      CASE(OP_LOADI_3, B) goto LOAD_I;
      CASE(OP_LOADI_4, B) goto LOAD_I;
      CASE(OP_LOADI_5, B) goto LOAD_I;
      CASE(OP_LOADI_6, B) goto LOAD_I;
      CASE(OP_LOADI_7, B) {
LOAD_I:
        SET_INT_VALUE(reg[a], insn - OP_LOADI_0);
        NEXT;
      }
      CASE(OP_RETURN, B) {
        return reg[a];
      }
      CASE(OP_ADD, B) {
        SET_INT_VALUE(reg[a], mrb_int(reg[a]) + mrb_int(reg[a + 1]));
        NEXT;
      }
      CASE(OP_ADDI, BB) {
        SET_INT_VALUE(reg[a], mrb_int(reg[a]) + b);
        NEXT;
      }
      CASE(OP_SUB, B) {
        SET_INT_VALUE(reg[a], mrb_int(reg[a]) - mrb_int(reg[a + 1]));
        NEXT;
      }
      CASE(OP_SUBI, BB) {
        SET_INT_VALUE(reg[a], mrb_int(reg[a]) - b);
        NEXT;
      }
      CASE(OP_MUL, B) {
        SET_INT_VALUE(reg[a], mrb_int(reg[a]) * mrb_int(reg[a + 1]));
        NEXT;
      }
      CASE(OP_DIV, B) {
        SET_INT_VALUE(reg[a], mrb_int(reg[a]) / mrb_int(reg[a + 1]));
        NEXT;
      }
      CASE(OP_EQ, B) {
        if(mrb_int(reg[a]) == mrb_int(reg[a + 1])) {
          SET_TRUE_VALUE(reg[a]);
        } else {
          SET_FALSE_VALUE(reg[a]);
        }
        NEXT;
      }
      CASE(OP_LT, B) {
        if(mrb_int(reg[a]) < mrb_int(reg[a + 1])) {
          SET_TRUE_VALUE(reg[a]);
        } else {
          SET_FALSE_VALUE(reg[a]);
        }
        NEXT;
      }
      CASE(OP_LE, B) {
        if(mrb_int(reg[a]) <= mrb_int(reg[a + 1])) {
          SET_TRUE_VALUE(reg[a]);
        } else {
          SET_FALSE_VALUE(reg[a]);
        }
        NEXT;
      }
      CASE(OP_GT, B) {
        if(mrb_int(reg[a]) > mrb_int(reg[a + 1])) {
          SET_TRUE_VALUE(reg[a]);
        } else {
          SET_FALSE_VALUE(reg[a]);
        }
        NEXT;
      }
      CASE(OP_GE, B) {
        if(mrb_int(reg[a]) >= mrb_int(reg[a + 1])) {
          SET_TRUE_VALUE(reg[a]);
        } else {
          SET_FALSE_VALUE(reg[a]);
        }
        NEXT;
      }
    }
  }

  // TODO: Next refactor to return nil
  mrb_value v;
  return v;
}
