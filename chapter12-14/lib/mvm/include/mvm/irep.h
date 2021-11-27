#ifndef MVM_IREP_H
#define MVM_IREP_H

#include<stdint.h>
#include<stdlib.h>

#define IREP_TYPE_SKIP    0
#define IREP_TYPE_LITERAL 1
#define IREP_TYPE_SYMBOL  2
#define IREP_TYPE_IREP    3

#define SKIP_PADDING() do {\
  size_t align = sizeof(uint32_t);\
  p += -(intptr_t)p & (align - 1);\
} while(0)

typedef struct irep_header {
  uint32_t size;
  uint16_t nlocals;
  uint16_t nregs;
  uint16_t nirep;
} irep_header;

irep_header* irep_read_header(const uint8_t* ptr, uint8_t* len);
const uint8_t* irep_get(const uint8_t* p, int type, int idx);

#endif
