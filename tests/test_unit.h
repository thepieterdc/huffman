/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_TEST_UNIT_H
#define HUFFMAN_TEST_UNIT_H

#include "../src/util/logging.h"

#define assertEquals(one, two) do { testunit_assertions++; if ((one) != (two)) return _testunit_assert_equals_failed(__func__, __LINE__, #one, #two); } while (0)
#define assertFalse(test) do { testunit_assertions++; if ((test)) return _testunit_assert_false_failed(__func__, __LINE__, #test); } while (0)
#define assertNotEquals(one, two) do { testunit_assertions++; if ((one) == (two)) return _testunit_assert_notequals_failed(__func__, __LINE__, #one, #two); } while (0)
#define assertNotNull(test) do { testunit_assertions++; if ((test) == NULL) return _testunit_assert_notnull_failed(__func__, __LINE__, #test); } while (0)
#define assertNull(test) do { testunit_assertions++; if ((test) != NULL) return _testunit_assert_null_failed(__func__, __LINE__, #test); } while (0)
#define assertTrue(test) do { testunit_assertions++; if (!(test)) return _testunit_assert_true_failed(__func__, __LINE__, #test); } while (0)

#define test(test) do { testunit_tests_total++; const char *message = test(); if (message) error_custom(message, false); else { success((const char*) #test); testunit_tests_ok++; } } while (0)

/** The amount of assertions. */
extern int testunit_assertions;
/** The amount of passed tests. */
extern int testunit_tests_ok;
/** The total amount of tests ran. */
extern int testunit_tests_total;

/**
 * Failed asserting two variables are equal.
 *
 * @param fn the function that failed
 * @param line the line that failed
 * @param one the first element of the comparison
 * @param two the second element of the comparison
 * @return message describing what went wrong
 */
const char *_testunit_assert_equals_failed(const char *fn, int line, const char *one, const char *two);

/**
 * Failed asserting a condition is false.
 *
 * @param fn the function that failed
 * @param line the line that failed
 * @param condition the condition that evaluated true
 * @return message describing what went wrong
 */
const char *_testunit_assert_false_failed(const char *fn, int line, const char *condition);

/**
 * Failed asserting two variables aren't equal.
 *
 * @param fn the function that failed
 * @param line the line that failed
 * @param one the first element of the comparison
 * @param two the second element of the comparison
 * @return message describing what went wrong
 */
const char *_testunit_assert_notequals_failed(const char *fn, int line, const char *one, const char *two);

/**
 * Failed asserting a variable is not null.
 *
 * @param fn the function that failed
 * @param line the line that failed
 * @param var the variable that was null
 * @return message describing what went wrong
 */
const char *_testunit_assert_notnull_failed(const char *fn, int line, const char *var);

/**
 * Failed asserting a variable is null.
 *
 * @param fn the function that failed
 * @param line the line that failed
 * @param var the variable that was not null
 * @return message describing what went wrong
 */
const char *_testunit_assert_null_failed(const char *fn, int line, const char *var);

/**
 * Failed asserting a condition is true.
 *
 * @param fn the function that failed
 * @param line the line that failed
 * @param condition the condition that evaluated false
 * @return message describing what went wrong
 */
const char *_testunit_assert_true_failed(const char *fn, int line, const char *condition);

#endif /* HUFFMAN_TEST_UNIT_H */