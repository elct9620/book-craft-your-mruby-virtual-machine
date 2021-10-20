#include "test_irep.h"

void test_irep_read_header() {
  const uint8_t bin[] = {
    0x00, 0x00, 0x01, 0x00, // Size = 255
    0x00, 0x04, // nlocals = 4
    0x00, 0x03, // nregs = 3
    0x00, 0x01, // nirep = 1
  };

  uint8_t len;

  irep_header* header = irep_read_header(bin, &len);

  TEST_ASSERT_EQUAL_UINT32(256, header->size);
  TEST_ASSERT_EQUAL_UINT16(4, header->nlocals);
  TEST_ASSERT_EQUAL_UINT16(3, header->nregs);
  TEST_ASSERT_EQUAL_UINT16(1, header->nirep);

  TEST_ASSERT_EQUAL(10, len);

  free(header);
}
