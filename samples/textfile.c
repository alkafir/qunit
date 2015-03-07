#include "../qunit.h"

QUNIT_TEST(test1) {
  qunit_pass();
}

QUNIT_TEST(test2) {
  qunit_pass();
}

QUNIT_TEST(test3) {
  qunit_fail();
}

int main() {
  QUNIT_TESTCASE tcase;

  qunit_tcase_init(&tcase);
  qunit_tcase_add(&tcase, test1);
  qunit_tcase_add(&tcase, test2);
  qunit_tcase_add(&tcase, test3);

  qunit_tcase_add_reporter(&tcase, qunit_reporter_console);
  qunit_tcase_add_reporter(&tcase, qunit_reporter_textfile);

  qunit_print_header();
  qunit_tcase_run(&tcase);

  return 0;
}
