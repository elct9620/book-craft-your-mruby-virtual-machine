#include "test_loop.h"

void test_while_loop() {
  const uint8_t bin[] = {
    /**
     * count = 0
     * while count < 5
     *   count += 1
     * end
     * count
     */
    0x52,0x49,0x54,0x45,0x30,0x30,0x30,0x37,0x85,0xd7,0x00,0x00,0x00,0x73,0x4d,0x41,
    0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x00,0x3e,0x30,0x30,
    0x30,0x32,0x00,0x00,0x00,0x8a,0x00,0x02,0x00,0x05,0x00,0x00,0x00,0x00,0x00,0x1c,
    0x06,0x01,0x21,0x00,0x0e,0x01,0x02,0x01,0x3c,0x02,0x01,0x01,0x01,0x02,0x01,0x02,
    0x01,0x0b,0x03,0x42,0x02,0x22,0x02,0x00,0x05,0x37,0x01,0x67,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x4c,0x56,0x41,0x52,0x00,0x00,0x00,0x17,0x00,0x00,0x00,0x01,
    0x00,0x05,0x63,0x6f,0x75,0x6e,0x74,0x00,0x00,0x00,0x01,0x45,0x4e,0x44,0x00,0x00,
    0x00,0x00,0x08,
  };

  mrb_state* mrb = mrb_open();
  mrb_value ret = mrb_exec(mrb, bin + 34);
  mrb_close(mrb);

  TEST_ASSERT_EQUAL_UINT32(MRB_TYPE_FIXNUM, ret.type);
  TEST_ASSERT_EQUAL_UINT32(5, ret.value.i);
}

/**
 * define loop method
 */
mrb_value c_loop(mrb_state* mrb) {
  const uint8_t* irep = (const uint8_t*)mrb->ci->argv->value.p;

  mrb_value ret;
  while(mrb->exc == 0) {
    ret = mrb_exec(mrb, irep);
  }
  mrb->exc = 1;

  return ret;
}

void test_c_loop() {
  const uint8_t bin[] = {
    /**
     * count = 0
     * loop do
     *   break if count >= 5
     *   count += 1
     * end
     * count
    */
    0x52,0x49,0x54,0x45,0x30,0x30,0x30,0x37,0x75,0x60,0x00,0x00,0x00,0xab,0x4d,0x41,
    0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x00,0x6f,0x30,0x30,
    0x30,0x32,0x00,0x00,0x00,0x59,0x00,0x02,0x00,0x04,0x00,0x01,0x00,0x00,0x00,0x0e,
    0x06,0x01,0x10,0x02,0x55,0x03,0x00,0x2f,0x02,0x00,0x00,0x37,0x01,0x67,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x04,0x6c,0x6f,0x6f,0x70,0x00,0x00,0x00,0x00,
    0x9e,0x00,0x02,0x00,0x05,0x00,0x00,0x00,0x00,0x00,0x21,0x00,0x33,0x00,0x00,0x00,
    0x1f,0x02,0x01,0x00,0x0b,0x03,0x45,0x02,0x23,0x02,0x00,0x14,0x0f,0x02,0x39,0x02,
    0x1f,0x02,0x01,0x00,0x3c,0x02,0x01,0x20,0x02,0x01,0x00,0x37,0x02,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x4c,0x56,0x41,0x52,0x00,0x00,0x00,0x1e,0x00,0x00,0x00,
    0x02,0x00,0x05,0x63,0x6f,0x75,0x6e,0x74,0x00,0x01,0x26,0x00,0x00,0x00,0x01,0x00,
    0x01,0x00,0x01,0x45,0x4e,0x44,0x00,0x00,0x00,0x00,0x08,

  };

  mrb_state* mrb = mrb_open();
  mrb_define_method(mrb->object_class, "loop", c_loop);
  mrb_value ret = mrb_exec(mrb, bin + 34);
  mrb_close(mrb);

  TEST_ASSERT_EQUAL_UINT32(MRB_TYPE_FIXNUM, ret.type);
  TEST_ASSERT_EQUAL_UINT32(6, ret.value.i);
}
