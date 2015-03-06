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

/*
 * Main function
 */
int main(int argc, char **argv) {
  QUNIT_TESTCASE tcase; /* Declare a test case */

  qunit_tcase_init(&tcase); /* Initialize the test case */

  /*
   * Add a reporter function to the test case.
   *
   * If no reporters are added to the test case, the test unit will
   * automatically add a console reporter to it.
   */
  qunit_tcase_add_reporter(&tcase, qunit_reporter_console);

  /*
   * Add tests to the test case
   */
  qunit_tcase_add(&tcase, test1);
  qunit_tcase_add(&tcase, test2);
  qunit_tcase_add(&tcase, test3);

  qunit_print_header(); /* Print the standard QUnit header */
  unsigned int failed = qunit_tcase_run(&tcase); /* Run the test case */
  
  printf("%u failed tests.\n", failed);

  return 0;
}
