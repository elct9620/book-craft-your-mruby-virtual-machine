#include<irep.h>
#include<opcode.h>

irep_header* irep_read_header(const uint8_t* p, uint8_t* len) {
  const uint8_t* start = p;

  irep_header* header = (irep_header*)malloc(sizeof(irep_header));

  header->size = READ_L();
  header->nlocals = READ_S();
  header->nregs = READ_S();
  header->nirep = READ_S();

  *len = (uint8_t)(p - start);

  return header;
}
