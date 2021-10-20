#include "test_vm.h"

void test_mrb_exec() {
  const uint8_t bin[] = {
    0x00, 0x00, 0x01, 0x00, // Size = 255
    0x00, 0x04, // nlocals = 4
    0x00, 0x03, // nregs = 3
    0x00, 0x01, // nirep = 1,
    0x00, 0x00, 0x00, 0x00, // Codelen = 0
    0x00, 0x00, // Padding to 16 bytes
    0x01 // OP_MOVE
  };

  int ret = mrb_exec(bin);

  TEST_ASSERT_EQUAL_UINT32(1, ret);
}
