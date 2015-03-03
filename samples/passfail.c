#include "../qunit.h"

QUNIT_TEST(test1) {
  qunit_pass();
}

QUNIT_TEST(test2) {
  qunit_fail();
}

QUNIT_TEST(test3) {
  int a = 10;
  qunit_assert(a == 10);
}

int main(int argc, char **argv) {
  QUNIT_TESTCASE tcase;

  qunit_tcase_init(&tcase);
  qunit_tcase_add_reporter(&tcase, qunit_reporter_console);

  qunit_tcase_add(&tcase, test1);
  qunit_tcase_add(&tcase, test2);
  qunit_tcase_add(&tcase, test3);

  qunit_print_header();
  unsigned int failed = qunit_tcase_run(&tcase);
  
  printf("%u failed tests.", failed);

  return 0;
}
