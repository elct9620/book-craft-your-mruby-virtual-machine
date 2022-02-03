#include "test_class.h"
#include "stdio.h"

/**
 * define run method
 */
mrb_value c_run(mrb_state* mrb, mrb_value self) {
  const char* str = "Hello World";
  return mrb_str_new((const uint8_t*)str, 12);
}

/**
 * Define Point class
 */
mrb_value point_initialize(mrb_state* mrb, mrb_value self) {
  mrb_iv_set(self, "@x", mrb->ci->argv[0]);
  mrb_iv_set(self, "@y", mrb->ci->argv[1]);

  return self;
}

mrb_value point_get_x(mrb_state* mrb, mrb_value self) {
  return mrb_iv_get(self, "@x");
}

mrb_value point_set_x(mrb_state* mrb, mrb_value self) {
  return mrb_iv_set(self, "@x", mrb->ci->argv[0]);
}

mrb_value point_to_string(mrb_state* mrb, mrb_value self) {
  char buffer[128];
  mrb_value x = mrb_iv_get(self, "@x");
  mrb_value y = mrb_iv_get(self, "@y");

  sprintf(buffer, "#<Point x=%d, y=%d>", mrb_fixnum(x), mrb_fixnum(y));
  return mrb_str_value(buffer);
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

void test_new_object() {
  const uint8_t bin[] = {
    // App.new
    0x52,0x49,0x54,0x45,0x30,0x30,0x30,0x37,0xe1,0xf7,0x00,0x00,0x00,0x56,0x4d,0x41,
    0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x00,0x38,0x30,0x30,
    0x30,0x32,0x00,0x00,0x00,0x4e,0x00,0x01,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x0a,
    0x1b,0x01,0x00,0x2e,0x01,0x01,0x00,0x37,0x01,0x67,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x02,0x00,0x03,0x41,0x70,0x70,0x00,0x00,0x03,0x6e,0x65,0x77,0x00,0x45,0x4e,
    0x44,0x00,0x00,0x00,0x00,0x08,
  };

  mrb_state* mrb = mrb_open();
  RClass* app = mrb_define_class(mrb, "App", mrb->object_class);

  mrb_value ret = mrb_exec(mrb, bin + 34);
  mrb_close(mrb);

  TEST_ASSERT_EQUAL_INT(MRB_TYPE_OBJECT, ret.type);
  TEST_ASSERT_EQUAL_INT(app, ((RObject*)ret.value.p)->c);
}

void test_new_object_with_arguments() {
  const uint8_t bin[] = {
    // point = Point.new(1, 1)
    // point.to_s
    0x52,0x49,0x54,0x45,0x30,0x30,0x30,0x37,0x2a,0x61,0x00,0x00,0x00,0x81,0x4d,0x41,
    0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x00,0x4c,0x30,0x30,
    0x30,0x32,0x00,0x00,0x00,0x83,0x00,0x02,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x15,
    0x1b,0x02,0x00,0x07,0x03,0x07,0x04,0x2e,0x02,0x01,0x02,0x01,0x01,0x02,0x2e,0x02,
    0x02,0x00,0x37,0x02,0x67,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x05,0x50,
    0x6f,0x69,0x6e,0x74,0x00,0x00,0x03,0x6e,0x65,0x77,0x00,0x00,0x04,0x74,0x6f,0x5f,
    0x73,0x00,0x4c,0x56,0x41,0x52,0x00,0x00,0x00,0x17,0x00,0x00,0x00,0x01,0x00,0x05,
    0x70,0x6f,0x69,0x6e,0x74,0x00,0x00,0x00,0x01,0x45,0x4e,0x44,0x00,0x00,0x00,0x00,
    0x08,
  };

  mrb_state* mrb = mrb_open();
  RClass* point = mrb_define_class(mrb, "Point", mrb->object_class);
  mrb_define_method(point, "initialize", point_initialize);
  mrb_define_method(point, "to_s", point_to_string);

  mrb_value ret = mrb_exec(mrb, bin + 34);
  mrb_close(mrb);

  TEST_ASSERT_EQUAL_STRING("#<Point x=1, y=1>", ret.value.p);
}

void test_object_call_method() {
  const uint8_t bin[] = {
    // app = App.new
    // app.run
    0x52,0x49,0x54,0x45,0x30,0x30,0x30,0x37,0xf2,0x7e,0x00,0x00,0x00,0x78,0x4d,0x41,
    0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x00,0x45,0x30,0x30,
    0x30,0x32,0x00,0x00,0x00,0x70,0x00,0x02,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x11,
    0x1b,0x02,0x00,0x2e,0x02,0x01,0x00,0x01,0x01,0x02,0x2e,0x02,0x02,0x00,0x37,0x02,
    0x67,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x03,0x41,0x70,0x70,0x00,0x00,
    0x03,0x6e,0x65,0x77,0x00,0x00,0x03,0x72,0x75,0x6e,0x00,0x4c,0x56,0x41,0x52,0x00,
    0x00,0x00,0x15,0x00,0x00,0x00,0x01,0x00,0x03,0x61,0x70,0x70,0x00,0x00,0x00,0x01,
    0x45,0x4e,0x44,0x00,0x00,0x00,0x00,0x08,
  };

  mrb_state* mrb = mrb_open();
  RClass* app = mrb_define_class(mrb, "App", mrb->object_class);
  mrb_define_method(app, "run", c_run);

  mrb_value ret = mrb_exec(mrb, bin + 34);
  mrb_close(mrb);

  TEST_ASSERT_EQUAL_STRING("Hello World", ret.value.p);
};

void test_object_call_parent_method() {
  const uint8_t bin[] = {
    // app = App.new
    // app.run
    0x52,0x49,0x54,0x45,0x30,0x30,0x30,0x37,0xf2,0x7e,0x00,0x00,0x00,0x78,0x4d,0x41,
    0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x00,0x45,0x30,0x30,
    0x30,0x32,0x00,0x00,0x00,0x70,0x00,0x02,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x11,
    0x1b,0x02,0x00,0x2e,0x02,0x01,0x00,0x01,0x01,0x02,0x2e,0x02,0x02,0x00,0x37,0x02,
    0x67,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x03,0x41,0x70,0x70,0x00,0x00,
    0x03,0x6e,0x65,0x77,0x00,0x00,0x03,0x72,0x75,0x6e,0x00,0x4c,0x56,0x41,0x52,0x00,
    0x00,0x00,0x15,0x00,0x00,0x00,0x01,0x00,0x03,0x61,0x70,0x70,0x00,0x00,0x00,0x01,
    0x45,0x4e,0x44,0x00,0x00,0x00,0x00,0x08,
  };

  mrb_state* mrb = mrb_open();
  RClass* base = mrb_define_class(mrb, "Base", mrb->object_class);
  mrb_define_method(base, "run", c_run);

  RClass* app = mrb_define_class(mrb, "App", base);

  mrb_value ret = mrb_exec(mrb, bin + 34);
  mrb_close(mrb);

  TEST_ASSERT_EQUAL_STRING("Hello World", ret.value.p);
};

void test_object_instance_variable() {
  const uint8_t bin[] = {
    // point = Point.new(0, 1)
    // point.x += 1
    // point.to_s
    0x52,0x49,0x54,0x45,0x30,0x30,0x30,0x37,0x14,0x20,0x00,0x00,0x00,0x9b,0x4d,0x41,
    0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x00,0x66,0x30,0x30,
    0x30,0x32,0x00,0x00,0x00,0xd0,0x00,0x02,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x26,
    0x1b,0x02,0x00,0x06,0x03,0x07,0x04,0x2e,0x02,0x01,0x02,0x01,0x01,0x02,0x01,0x03,
    0x02,0x2e,0x03,0x02,0x00,0x3c,0x03,0x01,0x2e,0x02,0x03,0x01,0x01,0x02,0x01,0x2e,
    0x02,0x04,0x00,0x37,0x02,0x67,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x00,0x05,
    0x50,0x6f,0x69,0x6e,0x74,0x00,0x00,0x03,0x6e,0x65,0x77,0x00,0x00,0x01,0x78,0x00,
    0x00,0x02,0x78,0x3d,0x00,0x00,0x04,0x74,0x6f,0x5f,0x73,0x00,0x4c,0x56,0x41,0x52,
    0x00,0x00,0x00,0x17,0x00,0x00,0x00,0x01,0x00,0x05,0x70,0x6f,0x69,0x6e,0x74,0x00,
    0x00,0x00,0x01,0x45,0x4e,0x44,0x00,0x00,0x00,0x00,0x08,
  };

  mrb_state* mrb = mrb_open();
  RClass* point = mrb_define_class(mrb, "Point", mrb->object_class);
  mrb_define_method(point, "initialize", point_initialize);
  mrb_define_method(point, "x", point_get_x);
  mrb_define_method(point, "x=", point_set_x);
  mrb_define_method(point, "to_s", point_to_string);

  mrb_value ret = mrb_exec(mrb, bin + 34);
  mrb_close(mrb);

  TEST_ASSERT_EQUAL_STRING("#<Point x=1, y=1>", ret.value.p);
}
