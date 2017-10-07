/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_TEST_UNIT_H
#define HUFFMAN_TEST_UNIT_H

#include "../src/util/logging.h"

#define assertThat(test) do { if (!(test)) return _testunit_assert_failed(__func__, __LINE__, #test); } while(0)
#define test(test) do { testunit_tests_total++; char* message = test(); if (message) warning(message); else { success((char*) #test); testunit_tests_ok++; } } while (0)

/** The amount of passed tests. */
extern int testunit_tests_ok;
/** The total amount of tests ran. */
extern int testunit_tests_total;

/**
 * An assertion has failed.
 *
 * @param fn the function that failed
 * @param line the line that failed
 * @param code the failed assertion
 * @return message describing what went wrong
 */
char *_testunit_assert_failed(const char *fn, int line, const char *code);

#endif /* HUFFMAN_TEST_UNIT_H */