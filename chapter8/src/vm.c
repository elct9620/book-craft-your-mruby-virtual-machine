#include<vm.h>
#include<opcode.h>

int mrb_exec(const uint8_t* bin) {
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
  intptr_t reg[irep->nregs];


  for(;;) {
    uint8_t insn = READ_B();

    switch(insn) {
      CASE(OP_NOP, Z) {
        NEXT;
      }
      CASE(OP_LOADI, BB) {
        reg[a] = b;
        NEXT;
      }
      CASE(OP_LOADINEG, BB) {
        reg[a] = b * -1;
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
        reg[a] = insn - OP_LOADI_0;
        NEXT;
      }
      CASE(OP_ADD, B) {
        reg[a] += reg[a + 1];
        NEXT;
      }
      CASE(OP_ADDI, BB) {
        reg[a] += b;
        NEXT;
      }
      CASE(OP_SUB, B) {
        reg[a] -= reg[a + 1];
        NEXT;
      }
      CASE(OP_SUBI, BB) {
        reg[a] -= b;
        NEXT;
      }
      CASE(OP_MUL, B) {
        reg[a] *= reg[a + 1];
        NEXT;
      }
      CASE(OP_DIV, B) {
        reg[a] /= reg[a + 1];
        NEXT;
      }
      CASE(OP_RETURN, B) {
        return reg[a];
      }
    }
  }

  return 0;
}
