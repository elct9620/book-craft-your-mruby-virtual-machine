#include<irep.h>

irep_header* irep_read_header(const uint8_t* ptr, uint8_t* len) {
  const uint8_t* start = ptr;

  irep_header* header = (irep_header*)malloc(sizeof(irep_header));

  header->size = bin_to_uint32(ptr);
  ptr += 4;

  header->nlocals = bin_to_uint16(ptr);
  ptr += 2;

  header->nregs = bin_to_uint16(ptr);
  ptr += 2;

  header->nirep = bin_to_uint16(ptr);
  ptr += 2;

  *len = (uint8_t)(ptr - start);

  return header;
}
