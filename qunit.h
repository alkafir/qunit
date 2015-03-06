/*
 * QUnit: Qafir's C unit test framework
 *    Copyright (C) 2015  Alfredo Mungo <alfredo.mungo@openmailbox.org>
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _QUNIT_H
#define _QUNIT_H

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

#define QUNIT_VERSION_MAJOR 0
#define QUNIT_VERSION_MINOR 2
#define QUNIT_VERSION_PATCH 0
#define __QUNIT_VERSION(__maj, __min, __pat) #__maj "." #__min "." #__pat
#define _QUNIT_VERSION(__maj, __min, __pat) __QUNIT_VERSION(__maj, __min, __pat)
#define QUNIT_VERSION _QUNIT_VERSION(QUNIT_VERSION_MAJOR, QUNIT_VERSION_MINOR, QUNIT_VERSION_PATCH)

/* Maximum number of tests per test case. Can be overridden in test files. */
#ifndef QUNIT_MAX_TESTS
  #define QUNIT_MAX_TESTS 64
#endif

/* Maximum number of reporters per test case. Can be overridden in test files. */
#ifndef QUNIT_MAX_REPORTERS
  #define QUNIT_MAX_REPORTERS 4
#endif

/* Default reporter for test case which do not define one. */
#ifndef QUNIT_DEFAULT_REPORTER
  #define QUNIT_DEFAULT_REPORTER qunit_reporter_console
#endif

/*
 * Test declaration macro.
 *
 * Substitutes to a test function declaration.
 *
 * __test_name: The name to assign to the test
 *
 * Example:
 *  QUNIT_TEST(myTest1) {
 *    ...
 *  }
 */
#define QUNIT_TEST(__test_name) void __test_name(QUNIT_RESULT *__qunit_result)

/*
 * Test registration macro.
 * 
 * Registers a test against a test case.
 *
 * __tcase: Pointer to the target test case
 * __test_func: Test function name
 *
 * Example:
 *  qunit_tcase_add(&tcase, myTest1);
 */
#define qunit_tcase_add(__tcase, __test_func) __qunit_tcase_add(__tcase, #__test_func, __test_func)

/*
 * Test pass macro.
 *
 * Immediately passes the current test.
 */
#define qunit_pass() *__qunit_result = QUNIT_RESULT_PASSED; return

/*
 * Test fail macro.
 *
 * Immediately fails the test.
 */
#define qunit_fail() *__qunit_result = QUNIT_RESULT_FAILED; return

/*
 * Condition assert macro.
 *
 * Fails the test if the given condition evaluates to 0.
 *
 * __code: Code representing a condition to evaluate
 *
 * Example:
 *  qunit_assert(1 == 5)
 */
#define qunit_assert(__code) if(!__code) qunit_fail()

/*
 * Error assert macro.
 *
 * Fails the test if the given error number is stored in `errno`.
 *
 * __errno: The error code to check against `errno`.
 *
 * Example:
 *  qunit_assert_errno(ERANGE)
 */
#define qunit_assert_errno(__errno) if(errno == __errno) qunit_fail()

/*
 * No error assert macro.
 *
 * Fails the test if `errno` is non-zero.
 */
#define qunit_assert_errno0() if(errno) qunit_fail()

/*
 * Vector equality assertion macro.
 *
 * Fails the test if the two provided vectors are not the same.
 * Equality is tested through a numerical equality comparison (operators ==, !=).
 *
 * __vec1: The first vector
 * __vec2: The second vector
 * __len: The length of the vectors
 *
 * Example:
 *  int a[] = {1, 2, 3};
 *  int b[] = {1, 2, 4};
 *
 *  qunit_assert_vector_equals(a, b, 3); <-- Will fail
 */
#define qunit_assert_vector_equals(__vec1, __vec2, __len) { size_t __i; for(__i = 0; __i < __len; __i++) if(__vec1[__i] != __vec2[__i]) qunit_fail(); } while(0)

/*
 * Vector equality assertion macro.
 *
 * Fails the test if the two provided vectors are not the same.
 * Equality is tested through a memory equality comparison (memcmp() function).
 *
 * __vec1: The first vector
 * __vec2: The second vector
 * __len: The length of the vectors
 * __sz: The size of the single element of the vectors
 *
 * Example:
 *  struct s{ int a; char b; };
 *  struct s a[] = {{1, 2}, {1, 3}};
 *  struct s b[] = {{1, 2}, {1, 3}};
 *
 *  qunit_assert_vector_equals2(a, b, 2, sizeof(struct s)); <-- Will pass
 *
 * See:
 *  qunit_assert_vector_equals3() for comparing the data of vectors of pointers.
 */
#define qunit_assert_vector_equals2(__vec1, __vec2, __len, __sz) { size_t __i; for(__i = 0; __i < __len; __i++) if(memcmp(&__vec1[__i], &__vec2[__i], __sz)) qunit_fail(); } while(0)

/*
 * Vector equality assertion macro.
 *
 * Fails the test if the two provided vectors are not the same.
 * Equality is tested through a memory equality comparison (memcmp() function).
 * Each element of the provided vectors must be a pointer to data of size `__sz`.
 *
 * __vec1: The first vector
 * __vec2: The second vector
 * __len: The length of the vectors
 * __sz: The size of the single element of the vectors
 *
 * Example:
 *  struct s{ int a; char b; };
 *  typedef struct s * s_ptr;
 *
 *  struct s s1 = {1, 2};
 *  struct s s2 = {1, 3};
 *
 *  s_ptr a[] = {&s1, &s2};
 *  s_ptr b[] = {&s1, &s2};
 *
 *  qunit_assert_vector_equals2(a, b, 2, sizeof(struct s));
 */
#define qunit_assert_vector_equals3(__vec1, __vec2, __len, __sz) { size_t __i; for(__i = 0; __i < __len; __i++) if(memcmp(__vec1[__i], __vec2[__i], __sz)) qunit_fail(); } while(0)

/*
 * Test result enumeration.
 */
typedef enum _QUNIT_RESULT {
  QUNIT_RESULT_PASSED = 0, /* Test passed */
  QUNIT_RESULT_FAILED = 1 /* Test failed */
} QUNIT_RESULT;

typedef void (*QUNIT_TESTFUNC)(QUNIT_RESULT*); /* Test function pointer */
typedef void (*QUNIT_REPORTERFUNC)(const char *, QUNIT_RESULT); /* Reporter function pointer */

/*
 * Test case structure.
 *
 * A test is a set of tests and reporters.
 *
 * The structure contains the following data about each test: function pointer, string name, result.
 */
typedef struct _QUNIT_TESTCASE {
  const char *names[QUNIT_MAX_TESTS];
  QUNIT_TESTFUNC tests[QUNIT_MAX_TESTS];
  QUNIT_RESULT results[QUNIT_MAX_TESTS];
  QUNIT_REPORTERFUNC reporters[QUNIT_MAX_REPORTERS];
} QUNIT_TESTCASE;

/*
 * Initializes a test case.
 *
 * tcase: Pointer to the test case to initialize
 */
void qunit_tcase_init(QUNIT_TESTCASE *tcase) {
  memset(tcase->tests, 0, sizeof(QUNIT_TESTFUNC) * QUNIT_MAX_TESTS);
  memset(tcase->reporters, 0, sizeof(QUNIT_REPORTERFUNC) * QUNIT_MAX_REPORTERS);
}

/*
 * Test case registration function.
 *
 * This function registers a test against a test case.
 *
 * tcase: The target test case
 * test_name: The test name
 * test_func: The test function pointer
 *
 * RETURN: 1 on success, 0 on failure
 * SEE: qunit_tcase_add()
 */
int __qunit_tcase_add(QUNIT_TESTCASE *tcase, const char* test_name, QUNIT_TESTFUNC test_func) {
  size_t i;

  for(i = 0; i < QUNIT_MAX_TESTS && tcase->tests[i] != 0; i++);

  if(i < QUNIT_MAX_TESTS) { /* Slot found */
    tcase->tests[i] = test_func;
    tcase->results[i] = QUNIT_RESULT_FAILED;
    tcase->names[i] = test_name;

    return 1;
  } else {
    fprintf(stderr, "WARNING: Could not add test \"%s\" to a testcase because it's full.\n\tPlease consider defining QUNIT_MAX_TESTS > %d.\n", test_name, (int)QUNIT_MAX_TESTS);
    return 0;
  }
}

/*
 * Adds a reporter to a test case.
 *
 * tcase: Target test case pointer
 * func: Reporter function pointer
 *
 * RETURN: 1 on success, 0 on failure
 */
int qunit_tcase_add_reporter(QUNIT_TESTCASE *tcase, QUNIT_REPORTERFUNC func) {
  size_t i;

  for(i = 0; i < QUNIT_MAX_REPORTERS && tcase->reporters[i] != 0; i++);

  if(i < QUNIT_MAX_REPORTERS) { /* Slot found */
    tcase->reporters[i] = func;
    return 1;
  } else {
    fprintf(stderr, "WARNING: Could not add reporter to a testcase because it's full.\n\tPlease consider defining QUNIT_MAX_REPORTERS > %d.\n", (int)QUNIT_MAX_REPORTERS);
    return 0;
  }
}

/*
 * Prints the QUnit program header.
 *
 * You can add the test version to the header by defining the TESTFILE_VERSION preprocessor constant.
 */
void qunit_print_header() {
  puts("Test file    : " __BASE_FILE__);
  #ifdef TESTFILE_VERSION
  puts("Test version : " TESTFILE_VERSION);
  #endif /* TESTFILE_VERSION */
  puts("QUnit version: " QUNIT_VERSION);
  puts("Compiled on  : " __DATE__);
  puts("");
}

/*
 * Console reporter function.
 *
 * This is a reporter function that outputs the test results to the console.
 *
 * name: The test name
 * result: The test result
 */
void qunit_reporter_console(const char* name, QUNIT_RESULT result) {
  const char* s_result = (result == QUNIT_RESULT_PASSED? "PASSED": "FAILED");

  printf("\t[%s] %s()\n", s_result, name);
}

/*
 * Runs a test case.
 *
 * Runs every test of the test case and after each test the reporter function is called to report the results.
 *
 * tcase: Pointer to the test case to run
 *
 * RETURN: The number of failed tests
 */
unsigned int qunit_tcase_run(QUNIT_TESTCASE *tcase) {
  size_t i, j;
  unsigned int failed = 0;

  if(!tcase->reporters[0])
    qunit_tcase_add_reporter(tcase, QUNIT_DEFAULT_REPORTER);
    
  for(i = 0; i < QUNIT_MAX_TESTS; i++) {
    if(tcase->tests[i]) {
      tcase->results[i] = QUNIT_RESULT_PASSED;
      tcase->tests[i](&(tcase->results[i]));

      for(j = 0; j < QUNIT_MAX_REPORTERS; j++)
        if(tcase->reporters[j])
          tcase->reporters[j](tcase->names[i], tcase->results[i]);
      
      if(tcase->results[i] == QUNIT_RESULT_FAILED)
        failed++;
    }
  }

  return failed;
}

#endif /* !_QUNIT_H */
