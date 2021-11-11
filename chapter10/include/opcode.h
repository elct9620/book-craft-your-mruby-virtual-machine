#ifndef MVM_OPCODE_H
#define MVM_OPCODE_H

/**
 * B = 8bit
 * S = 16bit
 * W = 24bit
 * L = 32bit
 */

#define PEEK_B(pc) (*(pc))
#define PEEK_S(pc) ((pc)[0]<<8|(pc)[1])
#define PEEK_W(pc) ((pc)[0]<<16|(pc)[1]<<8|(pc)[2])
#define PEEK_L(pc) ((pc)[0]<<24|(pc)[1]<<16|(pc)[2]<<8|(pc)[3])

#define READ_B() PEEK_B(p++)
#define READ_S() (p+=2, PEEK_S(p-2))
#define READ_W() (p+=3, PEEK_W(p-3))
#define READ_L() (p+=4, PEEK_L(p-4))

#define FETCH_Z() /* noop */
#define FETCH_B() do { a = READ_B(); } while(0)
#define FETCH_BB() do { a = READ_B(); b = READ_B(); } while(0)
#define FETCH_BBB() do { a = READ_B(); b = READ_B(); c = READ_B(); } while(0)
#define FETCH_BS() do { a = READ_B(); b = READ_S(); } while(0)
#define FETCH_S() do { a = READ_S(); } while(0)

enum {
  OP_NOP,
  OP_LOADI = 3,
  OP_LOADINEG,
  OP_LOADI__1,
  OP_LOADI_0,
  OP_LOADI_1,
  OP_LOADI_2,
  OP_LOADI_3,
  OP_LOADI_4,
  OP_LOADI_5,
  OP_LOADI_6,
  OP_LOADI_7,
  OP_LOADSELF = 16,
  OP_SEND = 46,
  OP_RETURN = 55,
  OP_ADD = 59,
  OP_ADDI,
  OP_SUB,
  OP_SUBI,
  OP_MUL,
  OP_DIV,
  OP_EQ,
  OP_LT,
  OP_LE,
  OP_GT,
  OP_GE,
  OP_STRING = 79,
};

#endif
