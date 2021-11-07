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

const uint8_t* irep_get(const uint8_t* p, int type, int idx) {
  READ_L(); // Size
  READ_S(); // nlocals
  READ_S(); // nregs
  uint16_t nirep = READ_S(); // nirep

  uint32_t codelen = READ_L();
  SKIP_PADDING();
  p += codelen;

  {
    uint32_t npool = READ_L();
    if (type == IREP_TYPE_LITERAL) {
      npool = idx;
    }

    for(int i = 0; i < npool; i++) {
      uint8_t type = READ_B();
      uint16_t size = READ_S();
      p += size;
    }

    if(type == IREP_TYPE_LITERAL) {
      return p;
    }
  }

  {
    uint32_t nsym = READ_L();
    if(type == IREP_TYPE_SYMBOL) {
      nsym = idx;
    }

    for(int i = 0; i < nsym; i++) {
      uint16_t size = READ_S();
      p += size;
    }

    if(type == IREP_TYPE_SYMBOL) {
      return p;
    }
  }

  {
    if(type == IREP_TYPE_IREP) {
      nirep = idx;
    }

    for(int i = 0; i < nirep; i++) {
      p = irep_get(p, IREP_TYPE_SKIP, 0);
    }

    if(type == IREP_TYPE_IREP) {
      return p;
    }
  }

  return p;
}
