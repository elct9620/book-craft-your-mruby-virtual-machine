#include<unity.h>

#include "test_utils.h"

void test_success() {
  TEST_ASSERT_TRUE(1);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_success);
  RUN_TEST(test_bin_to_uint8);
  return UNITY_END();
}
