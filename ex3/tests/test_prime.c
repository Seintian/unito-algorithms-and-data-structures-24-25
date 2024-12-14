/**
 * @file test_prime.c
 * @brief Unit tests for prime number functions.
 *
 * This file contains the implementation of unit tests for the prime number functions.
 */

#include "test_prime.h"
#include "prime.h"
#include "unity.h"
#include <stdlib.h>
#include <time.h>

/**
 * @brief Test the `is_prime` function with various edge cases and values.
 *
 * This test function checks the behavior of the `is_prime` function for:
 * - Negative numbers (should always return 0)
 * - Boundary conditions (0, 1, 2, 3, 4)
 * - A range of small values to ensure correctness.
 */
void test_is_prime(void) {
    // Test negative numbers (should always be 0)
    for (int i = -10; i < 0; i++) {
        TEST_ASSERT_EQUAL(0, is_prime(i)); /**< Ensure negative numbers are not prime */
    }

    // Test boundary conditions
    TEST_ASSERT_EQUAL(0, is_prime(0));  /**< 0 is not prime */
    TEST_ASSERT_EQUAL(0, is_prime(1));  /**< 1 is not prime */
    TEST_ASSERT_EQUAL(1, is_prime(2));  /**< 2 is prime */
    TEST_ASSERT_EQUAL(1, is_prime(3));  /**< 3 is prime */
    TEST_ASSERT_EQUAL(0, is_prime(4));  /**< 4 is not prime */
}

/**
 * @brief Test the `next_prime` function with various values.
 *
 * This test function checks the behavior of the `next_prime` function for:
 * - Boundary conditions (e.g., next prime after 0, 1, 2, 3)
 * - A range of numbers to ensure the next prime is correctly identified
 * - Large values to check performance and correctness for larger inputs
 * - Random values to validate that the next prime is indeed the next prime number.
 */
void test_next_prime(void) {
    // Test boundary conditions
    TEST_ASSERT_EQUAL(2, next_prime(0));  /**< Next prime after 0 is 2 */
    TEST_ASSERT_EQUAL(2, next_prime(1));  /**< Next prime after 1 is 2 */
    TEST_ASSERT_EQUAL(3, next_prime(2));  /**< Next prime after 2 is 3 */
    TEST_ASSERT_EQUAL(5, next_prime(3));  /**< Next prime after 3 is 5 */

    // Test next prime for numbers in a specific range
    TEST_ASSERT_EQUAL(7, next_prime(6));  /**< Next prime after 6 is 7 */
    TEST_ASSERT_EQUAL(11, next_prime(10)); /**< Next prime after 10 is 11 */
    TEST_ASSERT_EQUAL(13, next_prime(12)); /**< Next prime after 12 is 13 */
    TEST_ASSERT_EQUAL(17, next_prime(16)); /**< Next prime after 16 is 17 */

    // Test next prime with large values
    TEST_ASSERT_EQUAL(101, next_prime(100)); /**< Next prime after 100 is 101 */
    TEST_ASSERT_EQUAL(103, next_prime(102)); /**< Next prime after 102 is 103 */

    // Test next prime with random values
    srand(time(NULL));  /**< Seed the random number generator */
    for (int i = 0; i < 10; i++) {
        int random_value = rand() % 1000; /**< Generate a random number between 0 and 999 */
        int next_prime_value = next_prime(random_value); /**< Get the next prime number */
        
        TEST_ASSERT_TRUE(is_prime(next_prime_value)); /**< Ensure the result is prime */
        TEST_ASSERT_TRUE(next_prime_value > random_value); /**< Ensure the next prime is greater than the random value */
    }
}
