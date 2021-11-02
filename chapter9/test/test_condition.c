#include "test_condition.h"

void test_opcode_eq() {
  const uint8_t bin[] = {
    /**
     * # Ruby Code
     * 1 == 1
     */
  };

  mrb_value ret = mrb_exec(bin + 34);

  TEST_ASSERT_EQUAL_UINT32(1, ret.value.i);
}

void test_opcode_lt() {
  const uint8_t bin[] = {
    /**
     * # Ruby Code
     * 10 < 1
     */
  };

  mrb_value ret = mrb_exec(bin + 34);

  TEST_ASSERT_EQUAL_UINT32(0, ret.value.i);
}
void test_opcode_le() {
  const uint8_t bin[] = {
    /**
     * # Ruby Code
     * 1 <= 10
     */
  };

  mrb_value ret = mrb_exec(bin + 34);

  TEST_ASSERT_EQUAL_UINT32(1, ret.value.i);
}
void test_opcode_gt() {
  const uint8_t bin[] = {
    /**
     * # Ruby Code
     * 10 > 9
     */
  };

  mrb_value ret = mrb_exec(bin + 34);

  TEST_ASSERT_EQUAL_UINT32(1, ret.value.i);
}
void test_opcode_ge() {
  const uint8_t bin[] = {
    /**
     * # Ruby Code
     * 1 >= 9
     */
  };

  mrb_value ret = mrb_exec(bin + 34);

  TEST_ASSERT_EQUAL_UINT32(0, ret.value.i);
}

