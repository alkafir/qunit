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

#define QUNIT_VERSION_MAJOR 0
#define QUNIT_VERSION_MINOR 1
#define QUNIT_VERSION_PATCH 0
#define __QUNIT_VERSION(__maj, __min, __pat) #__maj "." #__min "." #__pat
#define _QUNIT_VERSION(__maj, __min, __pat) __QUNIT_VERSION(__maj, __min, __pat)
#define QUNIT_VERSION _QUNIT_VERSION(QUNIT_VERSION_MAJOR, QUNIT_VERSION_MINOR, QUNIT_VERSION_PATCH)

#ifndef QUNIT_MAX_TESTS
  #define QUNIT_MAX_TESTS 64
#endif

#ifndef QUNIT_MAX_REPORTERS
  #define QUNIT_MAX_REPORTERS 4
#endif

#define QUNIT_TEST(__test_name) void __test_name(QUNIT_RESULT *__qunit_result)

#define qunit_tcase_add(__tcase, __test_func) __qunit_tcase_add(__tcase, #__test_func, __test_func)

#define qunit_pass() *__qunit_result = QUNIT_RESULT_PASSED
#define qunit_fail() *__qunit_result = QUNIT_RESULT_FAILED

#define qunit_assert(__code) if(!__code) qunit_fail()

typedef enum _QUNIT_RESULT {
  QUNIT_RESULT_PASSED = 0,
  QUNIT_RESULT_FAILED = 1
} QUNIT_RESULT;

typedef void (*QUNIT_TESTFUNC)(QUNIT_RESULT*);
typedef void (*QUNIT_REPORTERFUNC)(const char *, QUNIT_RESULT);

typedef struct _QUNIT_TESTCASE {
  const char *names[QUNIT_MAX_TESTS];
  QUNIT_TESTFUNC tests[QUNIT_MAX_TESTS];
  QUNIT_RESULT results[QUNIT_MAX_TESTS];
  QUNIT_REPORTERFUNC reporters[QUNIT_MAX_REPORTERS];
} QUNIT_TESTCASE;

void qunit_tcase_init(QUNIT_TESTCASE *tcase) {
  memset(tcase->tests, 0, sizeof(QUNIT_TESTFUNC) * QUNIT_MAX_TESTS);
  memset(tcase->reporters, 0, sizeof(QUNIT_REPORTERFUNC) * QUNIT_MAX_REPORTERS);
}

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

void qunit_print_header() {
  puts("QUnit v" QUNIT_VERSION "\n");
}

unsigned int qunit_tcase_run(QUNIT_TESTCASE *tcase) {
  size_t i, j;
  unsigned int failed = 0;

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

void qunit_reporter_console(const char* name, QUNIT_RESULT result) {
  const char* s_result = (result == QUNIT_RESULT_PASSED? "PASSED": "FAILED");

  printf("\t[%s] %s()\n", s_result, name);
}

#endif /* !_QUNIT_H */
