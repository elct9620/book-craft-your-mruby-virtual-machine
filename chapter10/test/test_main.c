#include<unity.h>

#include "test_irep.h"
#include "test_vm.h"
#include "test_math.h"
#include "test_condition.h"

int main() {
  UNITY_BEGIN();

  // IREP
  RUN_TEST(test_irep_read_header);
  RUN_TEST(test_irep_get_literal);
  RUN_TEST(test_irep_get_symbol);

  // VM
  RUN_TEST(test_mrb_exec);

  // VM_Math
  RUN_TEST(test_opcode_loadi);
  RUN_TEST(test_opcode_loadineg);
  RUN_TEST(test_opcode_loadi__1);
  RUN_TEST(test_opcode_add);
  RUN_TEST(test_opcode_addi);
  RUN_TEST(test_opcode_sub);
  RUN_TEST(test_opcode_subi);
  RUN_TEST(test_opcode_mul);
  RUN_TEST(test_opcode_div);

  // VM_Condition
  RUN_TEST(test_opcode_eq);
  RUN_TEST(test_opcode_lt);
  RUN_TEST(test_opcode_le);
  RUN_TEST(test_opcode_gt);
  RUN_TEST(test_opcode_ge);

  return UNITY_END();
}
