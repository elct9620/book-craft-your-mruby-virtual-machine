#include<vm.h>

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

  return *p;
}
