#include "test_math.h"

void test_opcode_loadi() {
  const uint8_t bin[] = {
    /**
     * # Ruby Code
     * 99
     */
    0x52,0x49,0x54,0x45,0x30,0x30,0x30,0x37,0x01,0xfa,0x00,0x00,0x00,0x46,0x4d,0x41,
    0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x00,0x28,0x30,0x30,
    0x30,0x32,0x00,0x00,0x00,0x32,0x00,0x01,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x06,
    0x03,0x01,0x63,0x37,0x01,0x67,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x45,0x4e,
    0x44,0x00,0x00,0x00,0x00,0x08,
  };

  mrb_value ret = mrb_exec(bin + 34);

  TEST_ASSERT_EQUAL_UINT32(99, ret.value.i);
}

void test_opcode_loadineg() {
  const uint8_t bin[] = {
    /**
     * # Ruby Code
     * -101
     */
    0x52,0x49,0x54,0x45,0x30,0x30,0x30,0x37,0x89,0x07,0x00,0x00,0x00,0x46,0x4d,0x41,
    0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x00,0x28,0x30,0x30,
    0x30,0x32,0x00,0x00,0x00,0x32,0x00,0x01,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x06,
    0x04,0x01,0x65,0x37,0x01,0x67,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x45,0x4e,
    0x44,0x00,0x00,0x00,0x00,0x08,
  };

  mrb_value ret = mrb_exec(bin + 34);

  TEST_ASSERT_EQUAL_UINT32(-101, ret.value.i);
}

void test_opcode_loadi__1() {
  const uint8_t bin[] = {
    /**
     * # Ruby Code
     * -1
     */
    0x52,0x49,0x54,0x45,0x30,0x30,0x30,0x37,0xca,0xaa,0x00,0x00,0x00,0x45,0x4d,0x41,
    0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x00,0x27,0x30,0x30,
    0x30,0x32,0x00,0x00,0x00,0x2e,0x00,0x01,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x05,
    0x05,0x01,0x37,0x01,0x67,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x45,0x4e,0x44,
    0x00,0x00,0x00,0x00,0x08,
  };

  mrb_value ret = mrb_exec(bin + 34);

  TEST_ASSERT_EQUAL_UINT32(-1, ret.value.i);
}

void test_opcode_add() {
  const uint8_t bin[] = {
    /**
     * # Ruby Code
     * 1 + 100
     */
    0x52,0x49,0x54,0x45,0x30,0x30,0x30,0x37,0xb9,0x04,0x00,0x00,0x00,0x48,0x4d,0x41,
    0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x00,0x2a,0x30,0x30,
    0x30,0x32,0x00,0x00,0x00,0x3a,0x00,0x01,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x08,
    0x07,0x01,0x3c,0x01,0x64,0x37,0x01,0x67,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x45,0x4e,0x44,0x00,0x00,0x00,0x00,0x08,
  };

  mrb_value ret = mrb_exec(bin + 34);

  TEST_ASSERT_EQUAL_UINT32(101, ret.value.i);
}

void test_opcode_addi() {
  const uint8_t bin[] = {
    /**
     * # Ruby Code
     * 100 + 2
     */
    0x52,0x49,0x54,0x45,0x30,0x30,0x30,0x37,0x01,0x49,0x00,0x00,0x00,0x49,0x4d,0x41,
    0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x00,0x2b,0x30,0x30,
    0x30,0x32,0x00,0x00,0x00,0x3e,0x00,0x01,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x09,
    0x03,0x01,0x64,0x3c,0x01,0x02,0x37,0x01,0x67,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x45,0x4e,0x44,0x00,0x00,0x00,0x00,0x08,
  };

  mrb_value ret = mrb_exec(bin + 34);

  TEST_ASSERT_EQUAL_UINT32(102, ret.value.i);
}

void test_opcode_sub() {
  const uint8_t bin[] = {
    /**
     * # Ruby Code
     * 100 - 99
     */
    0x52,0x49,0x54,0x45,0x30,0x30,0x30,0x37,0x94,0x5e,0x00,0x00,0x00,0x49,0x4d,0x41,
    0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x00,0x2b,0x30,0x30,
    0x30,0x32,0x00,0x00,0x00,0x3e,0x00,0x01,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x09,
    0x03,0x01,0x64,0x3e,0x01,0x63,0x37,0x01,0x67,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x45,0x4e,0x44,0x00,0x00,0x00,0x00,0x08,
  };

  mrb_value ret = mrb_exec(bin + 34);

  TEST_ASSERT_EQUAL_UINT32(1, ret.value.i);
}

void test_opcode_subi() {
  const uint8_t bin[] = {
    /**
     * # Ruby Code
     * 100 - 1
     */
    0x52,0x49,0x54,0x45,0x30,0x30,0x30,0x37,0x6a,0x5d,0x00,0x00,0x00,0x49,0x4d,0x41,
    0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x00,0x2b,0x30,0x30,
    0x30,0x32,0x00,0x00,0x00,0x3e,0x00,0x01,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x09,
    0x03,0x01,0x64,0x3e,0x01,0x01,0x37,0x01,0x67,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x45,0x4e,0x44,0x00,0x00,0x00,0x00,0x08,
  };

  mrb_value ret = mrb_exec(bin + 34);

  TEST_ASSERT_EQUAL_UINT32(99, ret.value.i);
}

void test_opcode_mul() {
  const uint8_t bin[] = {
    /**
     * # Ruby Code
     * 10 * 10
     */
    0x52,0x49,0x54,0x45,0x30,0x30,0x30,0x37,0xe1,0x58,0x00,0x00,0x00,0x4b,0x4d,0x41,
    0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x00,0x2d,0x30,0x30,
    0x30,0x32,0x00,0x00,0x00,0x46,0x00,0x01,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x0b,
    0x03,0x01,0x0a,0x03,0x02,0x0a,0x3f,0x01,0x37,0x01,0x67,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x45,0x4e,0x44,0x00,0x00,0x00,0x00,0x08,
  };

  mrb_value ret = mrb_exec(bin + 34);

  TEST_ASSERT_EQUAL_UINT32(100, ret.value.i);
}

void test_opcode_div() {
  const uint8_t bin[] = {
    /**
     * # Ruby Code
     * 9 / 3
     */
    0x52,0x49,0x54,0x45,0x30,0x30,0x30,0x37,0xb4,0x99,0x00,0x00,0x00,0x4a,0x4d,0x41,
    0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x00,0x2c,0x30,0x30,
    0x30,0x32,0x00,0x00,0x00,0x42,0x00,0x01,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x0a,
    0x03,0x01,0x09,0x09,0x02,0x40,0x01,0x37,0x01,0x67,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x45,0x4e,0x44,0x00,0x00,0x00,0x00,0x08,
  };

  mrb_value ret = mrb_exec(bin + 34);

  TEST_ASSERT_EQUAL_UINT32(3, ret.value.i);
}
