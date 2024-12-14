/**
 * @file test_edit_distance.c
 * @brief Unit tests' implementation for the edit_distance algorithm.
 * 
 * This file contains the implementation of unit tests for the edit distance algorithms.
 */

#include "test_edit_distance.h"


/* Tests for edit_distance (recursive approach) */

/**
 * @brief Test the edit distance algorithm for identical strings using the recursive approach.
 * 
 * This test verifies that the recursive implementation correctly returns a distance of 0 when the input strings
 * are identical.
 */
void test_edit_distance_identical_strings_recursive(void) {
    TEST_ASSERT_EQUAL_INT(0, edit_distance("hello", "hello"));
}

/**
 * @brief Test the edit distance algorithm for empty string input using the recursive approach.
 * 
 * This test verifies that the recursive implementation correctly handles the case where one of the strings is empty,
 * and the distance is equal to the length of the non-empty string.
 */
void test_edit_distance_empty_string_recursive(void) {
    TEST_ASSERT_EQUAL_INT(5, edit_distance("hello", ""));
    TEST_ASSERT_EQUAL_INT(5, edit_distance("", "hello"));
}

/**
 * @brief Test the edit distance algorithm for insertion operation using the recursive approach.
 * 
 * This test verifies that the recursive implementation correctly calculates the edit distance when insertions are needed
 * to convert one string into another.
 */
void test_edit_distance_insertion_recursive(void) {
    TEST_ASSERT_EQUAL_INT(1, edit_distance("hello", "helloo"));
}

/**
 * @brief Test the edit distance algorithm for deletion operation using the recursive approach.
 * 
 * This test verifies that the recursive implementation correctly calculates the edit distance when deletions are needed
 * to convert one string into another.
 */
void test_edit_distance_deletion_recursive(void) {
    TEST_ASSERT_EQUAL_INT(1, edit_distance("helloo", "hello"));
}

/**
 * @brief Test the edit distance algorithm for substitution operation using the recursive approach.
 * 
 * This test verifies that the recursive implementation correctly calculates the edit distance when substitutions are needed
 * to convert one string into another.
 */
void test_edit_distance_substitution_recursive(void) {
    TEST_ASSERT_EQUAL_INT(2, edit_distance("hello", "jello"));
}

/**
 * @brief Test the edit distance algorithm for mixed operations using the recursive approach.
 * 
 * This test verifies that the recursive implementation correctly calculates the edit distance when a combination of insertions,
 * deletions, and substitutions are required to convert one string into another.
 */
void test_edit_distance_mixed_operations_recursive(void) {
    TEST_ASSERT_EQUAL_INT(4, edit_distance("sunday", "saturday"));
}

/**
 * @brief Test the edit distance algorithm for null string input using the recursive approach.
 * 
 * This test verifies that the recursive implementation correctly handles the case where one or both of the input strings
 * are null, returning an error code (-1).
 */
void test_edit_distance_null_string_recursive(void) {
    TEST_ASSERT_EQUAL_INT(-1, edit_distance(NULL, "test"));
    TEST_ASSERT_EQUAL_INT(-1, edit_distance("test", NULL));
}

/* Tests for edit_distance_dyn (dynamic programming approach) */

/**
 * @brief Test the edit distance algorithm for identical strings using the dynamic programming approach.
 * 
 * This test verifies that the dynamic programming implementation correctly returns a distance of 0 when the input strings
 * are identical.
 */
void test_edit_distance_identical_strings_dynamic(void) {
    TEST_ASSERT_EQUAL_INT(0, edit_distance_dyn("hello", "hello"));
}

/**
 * @brief Test the edit distance algorithm for empty string input using the dynamic programming approach.
 * 
 * This test verifies that the dynamic programming implementation correctly handles the case where one of the strings is empty,
 * and the distance is equal to the length of the non-empty string.
 */
void test_edit_distance_empty_string_dynamic(void) {
    TEST_ASSERT_EQUAL_INT(5, edit_distance_dyn("hello", ""));
    TEST_ASSERT_EQUAL_INT(5, edit_distance_dyn("", "hello"));
}

/**
 * @brief Test the edit distance algorithm for insertion operation using the dynamic programming approach.
 * 
 * This test verifies that the dynamic programming implementation correctly calculates the edit distance when insertions are needed
 * to convert one string into another.
 */
void test_edit_distance_insertion_dynamic(void) {
    TEST_ASSERT_EQUAL_INT(1, edit_distance_dyn("hello", "helloo"));
}

/**
 * @brief Test the edit distance algorithm for deletion operation using the dynamic programming approach.
 * 
 * This test verifies that the dynamic programming implementation correctly calculates the edit distance when deletions are needed
 * to convert one string into another.
 */
void test_edit_distance_deletion_dynamic(void) {
    TEST_ASSERT_EQUAL_INT(1, edit_distance_dyn("helloo", "hello"));
}

/**
 * @brief Test the edit distance algorithm for substitution operation using the dynamic programming approach.
 * 
 * This test verifies that the dynamic programming implementation correctly calculates the edit distance when substitutions are needed
 * to convert one string into another.
 */
void test_edit_distance_substitution_dynamic(void) {
    TEST_ASSERT_EQUAL_INT(2, edit_distance_dyn("hello", "jello"));
}

/**
 * @brief Test the edit distance algorithm for mixed operations using the dynamic programming approach.
 * 
 * This test verifies that the dynamic programming implementation correctly calculates the edit distance when a combination of insertions,
 * deletions, and substitutions are required to convert one string into another.
 */
void test_edit_distance_mixed_operations_dynamic(void) {
    TEST_ASSERT_EQUAL_INT(4, edit_distance_dyn("sunday", "saturday"));
}

/**
 * @brief Test the edit distance algorithm for null string input using the dynamic programming approach.
 * 
 * This test verifies that the dynamic programming implementation correctly handles the case where one or both of the input strings
 * are null, returning an error code (-1).
 */
void test_edit_distance_null_string_dynamic(void) {
    TEST_ASSERT_EQUAL_INT(-1, edit_distance_dyn(NULL, "test"));
    TEST_ASSERT_EQUAL_INT(-1, edit_distance_dyn("test", NULL));
}
