#include "../qunit.h"

QUNIT_TEST(vector_equals) {
  int a[] = {1, 2, 3};
  int b[] = {1, 2, 3};

  qunit_assert_vector_equals(a, b, 3);
}

QUNIT_TEST(vector_equals2) {
  struct s{ int a; char b; };
  struct s a[] = {{1, 2}, {1, 3}};
  struct s b[] = {{1, 2}, {1, 3}};

  qunit_assert_vector_equals2(a, b, 2, sizeof(struct s));
}

QUNIT_TEST(vector_equals3) {
  struct s{ int a; char b; };
  typedef struct s* s_ptr;

  struct s s1 = {1, 2};
  struct s s2 = {1, 3};

  s_ptr a[] = {&s1, &s2};
  s_ptr b[] = {&s1, &s2};

  qunit_assert_vector_equals3(a, b, 2, sizeof(struct s));
}

int main(int argc, char **argv) {
  QUNIT_TESTCASE tcase;

  qunit_tcase_init(&tcase);
  qunit_tcase_add(&tcase, vector_equals);
  qunit_tcase_add(&tcase, vector_equals2);
  qunit_tcase_add(&tcase, vector_equals3);

  qunit_print_header();
  return (int)qunit_tcase_run(&tcase);
}
