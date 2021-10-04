#include<stdio.h>
#include<stdlib.h>

enum {
  OP_NOP,
  OP_LOADI_0 = 6,
  OP_LOADI_1,
  OP_LOADI_2,
  OP_LOADI_3,
  OP_LOADI_4,
  OP_LOADI_5,
  OP_LOADI_6,
  OP_LOADI_7,
  OP_RETURN = 55,
  OP_ADDI = 60,
};

int main(int argc, char** argv) {
  int maxlen = 1024 * 100;
  uint8_t buf[maxlen];

  FILE* fp = fopen("add.mrb", "rb");
  int filelen = fread(buf, 1, maxlen, fp);


  uint8_t *bin = buf;
  // Skip RITE
  bin += 34;
  // Skip Header
  bin += 14;

  int32_t a = 0;
	int32_t b = 0;
	int32_t c = 0;
	intptr_t reg[4];

  for(;;) {
    uint8_t opcode = *bin++;
    switch(opcode) {
      case OP_NOP:
        break;
      case OP_LOADI_0:
      case OP_LOADI_1:
      case OP_LOADI_2:
      case OP_LOADI_3:
      case OP_LOADI_4:
      case OP_LOADI_5:
      case OP_LOADI_6:
      case OP_LOADI_7:
        a = *bin++;
        reg[a] = opcode - OP_LOADI_0;
        break;
      case OP_ADDI:
        a = *bin++;
        b = *bin++;
        reg[a] += b;
        break;
      case OP_RETURN:
        a = *bin++;
        printf("Result: %ld\n", reg[a]);
        return 0;
    }
  }

  fclose(fp);

  return 0;
}
