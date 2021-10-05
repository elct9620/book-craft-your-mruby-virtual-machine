#include<unity.h>

void test_success() {
  TEST_ASSERT_TRUE(1);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_success);
  return UNITY_END();
}
