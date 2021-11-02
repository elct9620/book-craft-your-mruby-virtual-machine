#include "test_condition.h"

void test_opcode_eq() {
  const uint8_t bin[] = {
    /**
     * # Ruby Code
     * 1 == 1
     */
  };

  int ret = mrb_exec(bin + 34);

  TEST_ASSERT_EQUAL_UINT32(1, ret);
}

void test_opcode_lt() {
  const uint8_t bin[] = {
    /**
     * # Ruby Code
     * 10 < 1
     */
  };

  int ret = mrb_exec(bin + 34);

  TEST_ASSERT_EQUAL_UINT32(0, ret);
}
void test_opcode_le() {
  const uint8_t bin[] = {
    /**
     * # Ruby Code
     * 1 <= 10
     */
  };

  int ret = mrb_exec(bin + 34);

  TEST_ASSERT_EQUAL_UINT32(1, ret);
}
void test_opcode_gt() {
  const uint8_t bin[] = {
    /**
     * # Ruby Code
     * 10 > 9
     */
  };

  int ret = mrb_exec(bin + 34);

  TEST_ASSERT_EQUAL_UINT32(1, ret);
}
void test_opcode_ge() {
  const uint8_t bin[] = {
    /**
     * # Ruby Code
     * 1 >= 9
     */
  };

  int ret = mrb_exec(bin + 34);

  TEST_ASSERT_EQUAL_UINT32(0, ret);
}

