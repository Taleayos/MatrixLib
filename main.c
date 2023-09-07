#include "test_matrix.h"

int main(void) {
  Suite *pS = test_matrix();
  SRunner *sr = srunner_create(pS);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
  return 0;
}
