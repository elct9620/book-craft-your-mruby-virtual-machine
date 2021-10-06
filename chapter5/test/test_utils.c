#include "test_utils.h"

void test_bin_to_uint8() {
  const uint8_t data[1] = { 0x01 };
  TEST_ASSERT_EQUAL_UINT8(1, bin_to_uint8(data));

  const uint8_t data2[2] = { 0xFF, 0x01 };
  TEST_ASSERT_EQUAL_UINT8(255, bin_to_uint8(data2));
}
