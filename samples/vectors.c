#include "../qunit.h"

QUNIT_TEST(vector_equals) {
  int a[] = {1, 2, 3};
  int b[] = {1, 2, 3};

  qunit_assert_vector_equals(a, b, 3);
}

QUNIT_TEST(vector_equals2) {
  unsigned int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
  unsigned int b[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

  qunit_assert_vector_equals2(a, b, 10, sizeof(unsigned int));
}

int main(int argc, char **argv) {
  QUNIT_TESTCASE tcase;

  qunit_tcase_init(&tcase);
  qunit_tcase_add(&tcase, vector_equals);
  qunit_tcase_add(&tcase, vector_equals2);

  qunit_print_header();
  return (int)qunit_tcase_run(&tcase);
}
