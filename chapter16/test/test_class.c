#include "test_class.h"

/**
 * define run method
 */
mrb_value c_run(mrb_state* mrb) {
  const char* str = "Hello World";
  return mrb_str_new((const uint8_t*)str, 12);
}

void test_define_class() {
  const uint8_t bin[] = {
    // App.run
    0x52,0x49,0x54,0x45,0x30,0x30,0x30,0x37,0xa5,0x5c,0x00,0x00,0x00,0x56,0x4d,0x41,
    0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x00,0x38,0x30,0x30,
    0x30,0x32,0x00,0x00,0x00,0x4e,0x00,0x01,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x0a,
    0x1b,0x01,0x00,0x2e,0x01,0x01,0x00,0x37,0x01,0x67,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x02,0x00,0x03,0x41,0x70,0x70,0x00,0x00,0x03,0x72,0x75,0x6e,0x00,0x45,0x4e,
    0x44,0x00,0x00,0x00,0x00,0x08,
  };

  mrb_state* mrb = mrb_open();
  RClass* app = mrb_define_class(mrb, "App", mrb->object_class);
  mrb_define_method(app, "run", c_run);

  mrb_value ret = mrb_exec(mrb, bin + 34);
  mrb_close(mrb);

  TEST_ASSERT_EQUAL_STRING("Hello World", ret.value.p);
}

void test_define_class_with_parent() {
  const uint8_t bin[] = {
    // App.run
    0x52,0x49,0x54,0x45,0x30,0x30,0x30,0x37,0xa5,0x5c,0x00,0x00,0x00,0x56,0x4d,0x41,
    0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x00,0x38,0x30,0x30,
    0x30,0x32,0x00,0x00,0x00,0x4e,0x00,0x01,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x0a,
    0x1b,0x01,0x00,0x2e,0x01,0x01,0x00,0x37,0x01,0x67,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x02,0x00,0x03,0x41,0x70,0x70,0x00,0x00,0x03,0x72,0x75,0x6e,0x00,0x45,0x4e,
    0x44,0x00,0x00,0x00,0x00,0x08,
  };

  mrb_state* mrb = mrb_open();
  RClass* base = mrb_define_class(mrb, "Base", mrb->object_class);
  mrb_define_method(base, "run", c_run);

  RClass* app = mrb_define_class(mrb, "App", base);

  mrb_value ret = mrb_exec(mrb, bin + 34);
  mrb_close(mrb);

  TEST_ASSERT_EQUAL_STRING("Hello World", ret.value.p);
}
