#include<stdio.h>
#include<mvm.h>

extern mrb_state* mrb_open() {
  static const mrb_state mrb_state_zero = { 0 };
  mrb_state* mrb = (mrb_state*)malloc(sizeof(mrb_state));

  *mrb = mrb_state_zero;
  mrb->mt = kh_init(mt);

  return mrb;
}

extern void mrb_close(mrb_state* mrb) {
  if(!mrb) return;

  kh_destroy(mt, mrb->mt);
  free(mrb);
}

mrb_value mrb_exec(mrb_state* mrb, const uint8_t* bin) {
  const uint8_t* p = bin;
  uint8_t len;

  irep_header* irep = irep_read_header(p, &len);
  p += len;

  READ_L(); // codelen
  SKIP_PADDING();

  // Register
  int32_t a = 0;
  int32_t b = 0;
  int32_t c = 0;
  const uint8_t* prog = p;
  mrb_value stack[irep->nregs];

  for(;;) {
    uint8_t insn = READ_B();

    switch(insn) {
      CASE(OP_NOP, Z) {
        NEXT;
      }
      CASE(OP_MOVE, BB) {
        stack[a] = stack[b];
        NEXT;
      }
      CASE(OP_LOADI, BB) {
        SET_INT_VALUE(stack[a], b);
        NEXT;
      }
      CASE(OP_LOADINEG, BB) {
        SET_INT_VALUE(stack[a], b * -1);
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
        SET_INT_VALUE(stack[a], insn - OP_LOADI_0);
        NEXT;
      }
      CASE(OP_LOADNIL, B) {
        stack[a] = mrb_nil_value();
        NEXT;
      }
      CASE(OP_LOADSELF, B) {
        // TODO
        NEXT;
      }
      CASE(OP_LOADT, B) goto L_LOADF;
      CASE(OP_LOADF, B) {
L_LOADF:
        stack[a] = mrb_nil_value();
        if(insn == OP_LOADT) {
          SET_TRUE_VALUE(stack[a]);
        } else {
          SET_FALSE_VALUE(stack[a]);
        }
        NEXT;
      }
      CASE(OP_JMP, S) {
        p = prog + a;
        NEXT;
      }
      CASE(OP_JMPIF, BS) {
        if (!IS_FALSE_VALUE(stack[a])) {
          p = prog + b;
        }
        NEXT;
      }
      CASE(OP_JMPNOT, BS) {
        if (IS_FALSE_VALUE(stack[a])) {
          p = prog + b;
        }
        NEXT;
      }
      CASE(OP_JMPNIL, BS) {
        if (IS_FALSE_VALUE(stack[a]) && !mrb_fixnum(stack[a])) {
          p = prog + b;
        }
        NEXT;
      }
      CASE(OP_SEND, BBB) {
        const uint8_t* sym = irep_get(bin, IREP_TYPE_SYMBOL, b);
        int len = PEEK_S(sym);
        mrb_value method_name = mrb_str_new(sym + 2, len);

        mrb_callinfo ci = {
          .argc = c,
          .argv = &stack[a + 1]
        };

        mrb->ci = &ci;

        khiter_t key = kh_get(mt, mrb->mt, (char *)method_name.value.p);
        if(key != kh_end(mrb->mt)) {
          mrb_func_t func = kh_value(mrb->mt, key);
          func(mrb);
        } else if(strcmp("puts", method_name.value.p) == 0) {
#ifndef UNIT_TEST
          printf("%s\n", (char *)stack[a + 1].value.p);
#endif
          stack[a] = stack[a + 1];
        } else {
          SET_NIL_VALUE(stack[a]);
        }

        mrb->ci = NULL;
        free(method_name.value.p);
        NEXT;
      }
      CASE(OP_SENDB, BBB) {
        const uint8_t* sym = irep_get(bin, IREP_TYPE_SYMBOL, b);
        int len = PEEK_S(sym);
        mrb_value method_name = mrb_str_new(sym + 2, len);

        khiter_t key = kh_get(mt, mrb->mt, (char *)method_name.value.p);
        if(key != kh_end(mrb->mt)) {
          mrb_func_t func = kh_value(mrb->mt, key);

          mrb_value argv[c + 1];
          for(int i = 0; i <= c; i++) {
            argv[i] = stack[a + i + 1];
          }

          mrb_callinfo ci = { .argc = c + 1, .argv = argv };
          mrb->ci = &ci;

          func(mrb);
        } else {
          SET_NIL_VALUE(stack[a]);
        }

        mrb->ci = NULL;
        free(method_name.value.p);

        NEXT;
      }
      CASE(OP_ENTER, W) {
        // TODO
        NEXT;
      }
      CASE(OP_RETURN, B) {
        return stack[a];
      }
      CASE(OP_BREAK, B) {
        mrb->exc = 1;
        NEXT;
      }
      CASE(OP_ADD, B) {
        SET_INT_VALUE(stack[a], mrb_int(stack[a]) + mrb_int(stack[a + 1]));
        NEXT;
      }
      CASE(OP_ADDI, BB) {
        SET_INT_VALUE(stack[a], mrb_int(stack[a]) + b);
        NEXT;
      }
      CASE(OP_SUB, B) {
        SET_INT_VALUE(stack[a], mrb_int(stack[a]) - mrb_int(stack[a + 1]));
        NEXT;
      }
      CASE(OP_SUBI, BB) {
        SET_INT_VALUE(stack[a], mrb_int(stack[a]) - b);
        NEXT;
      }
      CASE(OP_MUL, B) {
        SET_INT_VALUE(stack[a], mrb_int(stack[a]) * mrb_int(stack[a + 1]));
        NEXT;
      }
      CASE(OP_DIV, B) {
        SET_INT_VALUE(stack[a], mrb_int(stack[a]) / mrb_int(stack[a + 1]));
        NEXT;
      }
      CASE(OP_EQ, B) {
        if(mrb_int(stack[a]) == mrb_int(stack[a + 1])) {
          SET_TRUE_VALUE(stack[a]);
        } else {
          SET_FALSE_VALUE(stack[a]);
        }
        NEXT;
      }
      CASE(OP_LT, B) {
        if(mrb_int(stack[a]) < mrb_int(stack[a + 1])) {
          SET_TRUE_VALUE(stack[a]);
        } else {
          SET_FALSE_VALUE(stack[a]);
        }
        NEXT;
      }
      CASE(OP_LE, B) {
        if(mrb_int(stack[a]) <= mrb_int(stack[a + 1])) {
          SET_TRUE_VALUE(stack[a]);
        } else {
          SET_FALSE_VALUE(stack[a]);
        }
        NEXT;
      }
      CASE(OP_GT, B) {
        if(mrb_int(stack[a]) > mrb_int(stack[a + 1])) {
          SET_TRUE_VALUE(stack[a]);
        } else {
          SET_FALSE_VALUE(stack[a]);
        }
        NEXT;
      }
      CASE(OP_GE, B) {
        if(mrb_int(stack[a]) >= mrb_int(stack[a + 1])) {
          SET_TRUE_VALUE(stack[a]);
        } else {
          SET_FALSE_VALUE(stack[a]);
        }
        NEXT;
      }
      CASE(OP_STRING, BB) {
        const uint8_t* lit = irep_get(bin, IREP_TYPE_LITERAL, b);
        lit += 1; // Skip Type
        int len = PEEK_S(lit);
        lit += 2;

        stack[a] = mrb_str_new(lit, len);

        NEXT;
      }
      CASE(OP_BLOCK, BB) {
        mrb_value proc;
        proc.type = MRB_TYPE_PROC;
        proc.value.p = (void*)irep_get(bin, IREP_TYPE_IREP, b);
        stack[a] = proc;
        NEXT;
      }
    }
  }

  return mrb_nil_value();
}
