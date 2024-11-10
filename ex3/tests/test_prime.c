/**
 * @file test_prime.c
 * @brief Unit tests for prime number functions.
 */

#include "test_prime.h"
#include "prime.h"
#include "unity.h"


void test_is_prime(void) {
    TEST_ASSERT_EQUAL(0, is_prime(0));
    TEST_ASSERT_EQUAL(0, is_prime(1));
    TEST_ASSERT_EQUAL(1, is_prime(2));
    TEST_ASSERT_EQUAL(1, is_prime(3));
    TEST_ASSERT_EQUAL(0, is_prime(4));
    TEST_ASSERT_EQUAL(1, is_prime(5));
    TEST_ASSERT_EQUAL(0, is_prime(6));
    TEST_ASSERT_EQUAL(1, is_prime(7));
    TEST_ASSERT_EQUAL(0, is_prime(8));
    TEST_ASSERT_EQUAL(0, is_prime(9));
    TEST_ASSERT_EQUAL(0, is_prime(10));
    TEST_ASSERT_EQUAL(1, is_prime(11));
    TEST_ASSERT_EQUAL(0, is_prime(12));
    TEST_ASSERT_EQUAL(1, is_prime(13));
    TEST_ASSERT_EQUAL(0, is_prime(14));
    TEST_ASSERT_EQUAL(0, is_prime(15));
    TEST_ASSERT_EQUAL(0, is_prime(16));
    TEST_ASSERT_EQUAL(1, is_prime(17));
    TEST_ASSERT_EQUAL(0, is_prime(18));
    TEST_ASSERT_EQUAL(1, is_prime(19));
    TEST_ASSERT_EQUAL(0, is_prime(20));
    TEST_ASSERT_EQUAL(0, is_prime(21));
    TEST_ASSERT_EQUAL(0, is_prime(22));
    TEST_ASSERT_EQUAL(1, is_prime(23));
    TEST_ASSERT_EQUAL(0, is_prime(24));
    TEST_ASSERT_EQUAL(0, is_prime(25));
    TEST_ASSERT_EQUAL(0, is_prime(26));
    TEST_ASSERT_EQUAL(0, is_prime(27));
    TEST_ASSERT_EQUAL(0, is_prime(28));
    TEST_ASSERT_EQUAL(1, is_prime(29));
    TEST_ASSERT_EQUAL(0, is_prime(30));
    TEST_ASSERT_EQUAL(1, is_prime(31));
    TEST_ASSERT_EQUAL(0, is_prime(32));
    TEST_ASSERT_EQUAL(0, is_prime(33));
    TEST_ASSERT_EQUAL(0, is_prime(34));
    TEST_ASSERT_EQUAL(0, is_prime(35));
    TEST_ASSERT_EQUAL(0, is_prime(36));
    TEST_ASSERT_EQUAL(1, is_prime(37));
    TEST_ASSERT_EQUAL(0, is_prime(38));
    TEST_ASSERT_EQUAL(0, is_prime(39));
    TEST_ASSERT_EQUAL(0, is_prime(40));
    TEST_ASSERT_EQUAL(1, is_prime(41));
}

void test_next_prime(void) {
    TEST_ASSERT_EQUAL(2, next_prime(0));
    TEST_ASSERT_EQUAL(2, next_prime(1));
    TEST_ASSERT_EQUAL(3, next_prime(2));
    TEST_ASSERT_EQUAL(5, next_prime(3));
    TEST_ASSERT_EQUAL(5, next_prime(4));
    TEST_ASSERT_EQUAL(7, next_prime(5));
    TEST_ASSERT_EQUAL(7, next_prime(6));
    TEST_ASSERT_EQUAL(11, next_prime(7));
    TEST_ASSERT_EQUAL(11, next_prime(8));
    TEST_ASSERT_EQUAL(11, next_prime(9));
    TEST_ASSERT_EQUAL(11, next_prime(10));
    TEST_ASSERT_EQUAL(13, next_prime(11));
    TEST_ASSERT_EQUAL(13, next_prime(12));
    TEST_ASSERT_EQUAL(17, next_prime(13));
    TEST_ASSERT_EQUAL(17, next_prime(14));
    TEST_ASSERT_EQUAL(17, next_prime(15));
    TEST_ASSERT_EQUAL(17, next_prime(16));
    TEST_ASSERT_EQUAL(19, next_prime(17));
    TEST_ASSERT_EQUAL(19, next_prime(18));
    TEST_ASSERT_EQUAL(23, next_prime(19));
    TEST_ASSERT_EQUAL(23, next_prime(20));
    TEST_ASSERT_EQUAL(23, next_prime(21));
    TEST_ASSERT_EQUAL(23, next_prime(22));
    TEST_ASSERT_EQUAL(29, next_prime(23));
    TEST_ASSERT_EQUAL(29, next_prime(24));
    TEST_ASSERT_EQUAL(29, next_prime(25));
    TEST_ASSERT_EQUAL(29, next_prime(26));
    TEST_ASSERT_EQUAL(29, next_prime(27));
    TEST_ASSERT_EQUAL(29, next_prime(28));
    TEST_ASSERT_EQUAL(31, next_prime(29));
    TEST_ASSERT_EQUAL(31, next_prime(30));
    TEST_ASSERT_EQUAL(37, next_prime(31));
    TEST_ASSERT_EQUAL(37, next_prime(32));
    TEST_ASSERT_EQUAL(37, next_prime(33));
    TEST_ASSERT_EQUAL(37, next_prime(34));
    TEST_ASSERT_EQUAL(37, next_prime(35));
    TEST_ASSERT_EQUAL(37, next_prime(36));
    TEST_ASSERT_EQUAL(41, next_prime(37));
    TEST_ASSERT_EQUAL(41, next_prime(38));
    TEST_ASSERT_EQUAL(41, next_prime(39));
    TEST_ASSERT_EQUAL(41, next_prime(40));
}