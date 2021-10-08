#include<unity.h>

#include "test_utils.h"
#include "test_irep.h"

int main() {
  UNITY_BEGIN();

  // Utils
  RUN_TEST(test_bin_to_uint8);
  RUN_TEST(test_bin_to_uint8);
  RUN_TEST(test_bin_to_uint8);

  // IREP
  RUN_TEST(test_irep_read_header);

  return UNITY_END();
}
