#include "test_utils.h"

void test_bin_to_uint8() {
  const uint8_t data[1] = { 0x01 };
  TEST_ASSERT_EQUAL_UINT8(1, bin_to_uint8(data));

  const uint8_t data2[2] = { 0xFF, 0x01 };
  TEST_ASSERT_EQUAL_UINT8(255, bin_to_uint8(data2));
}

void test_bin_to_uint16() {
  const uint8_t data[2] = { 0x01, 0x02 };
  TEST_ASSERT_EQUAL_UINT8(257, bin_to_uint16(data));

  const uint8_t data2[3] = { 0x01, 0x03, 0xFF };
  TEST_ASSERT_EQUAL_UINT8(258, bin_to_uint8(data2));
}

void test_bin_to_uint32() {
  const uint8_t data[4] = { 0x00, 0x00, 0x01, 0x02 };
  TEST_ASSERT_EQUAL_UINT8(257, bin_to_uint32(data));

  const uint8_t data2[5] = { 0x00, 0x00, 0x01, 0x03, 0xFF };
  TEST_ASSERT_EQUAL_UINT8(258, bin_to_uint8(data2));
}
