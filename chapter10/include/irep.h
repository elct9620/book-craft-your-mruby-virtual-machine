#ifndef MVM_IREP_H
#define MVM_IREP_H

#include<stdint.h>
#include<stdlib.h>

typedef struct irep_header {
  uint32_t size;
  uint16_t nlocals;
  uint16_t nregs;
  uint16_t nirep;
} irep_header;

irep_header* irep_read_header(const uint8_t* ptr, uint8_t* len);

#endif
