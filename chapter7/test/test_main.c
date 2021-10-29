#include<unity.h>

#include "test_utils.h"
#include "test_irep.h"
#include "test_vm.h"
#include "test_math.h"

int main() {
  UNITY_BEGIN();

  // Utils
  RUN_TEST(test_bin_to_uint8);
  RUN_TEST(test_bin_to_uint8);
  RUN_TEST(test_bin_to_uint8);

  // IREP
  RUN_TEST(test_irep_read_header);

  // VM
  RUN_TEST(test_mrb_exec);

  // VM_Math
  RUN_TEST(test_opcode_loadi);
  RUN_TEST(test_opcode_loadineg);
  RUN_TEST(test_opcode_loadi__1);

  return UNITY_END();
}
