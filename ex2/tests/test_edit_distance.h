/**
 * @file test_edit_distance.h
 * @brief Unit tests for the edit_distance algorithm.
 * 
 * This file contains the declarations of unit tests for the edit distance algorithm, which calculates the minimum
 * number of operations (insertions, deletions) required to convert one string into another.
 * The tests are divided into two categories: recursive and dynamic programming implementations of the algorithm.
 * Each test function verifies a specific case or behavior of the edit distance algorithm.
 * 
 * @see edit_distance.h
 */

#include "unity.h"
#include "edit_distance.h"

#ifndef _TEST_EDIT_DISTANCE_H
#define _TEST_EDIT_DISTANCE_H

/**
 * @brief Test the edit distance algorithm for identical strings using the recursive approach.
 * 
 * This test verifies that the recursive implementation correctly returns a distance of 0 when the input strings
 * are identical.
 */
void test_edit_distance_identical_strings_recursive(void);

/**
 * @brief Test the edit distance algorithm for an empty string using the recursive approach.
 * 
 * This test verifies that the recursive implementation correctly handles the case where one of the strings is empty,
 * and the distance is equal to the length of the non-empty string.
 */
void test_edit_distance_empty_string_recursive(void);

/**
 * @brief Test the edit distance algorithm for insertion operation using the recursive approach.
 * 
 * This test verifies that the recursive implementation correctly calculates the edit distance when insertions are needed
 * to convert one string into another.
 */
void test_edit_distance_insertion_recursive(void);

/**
 * @brief Test the edit distance algorithm for deletion operation using the recursive approach.
 * 
 * This test verifies that the recursive implementation correctly calculates the edit distance when deletions are needed
 * to convert one string into another.
 */
void test_edit_distance_deletion_recursive(void);

/**
 * @brief Test the edit distance algorithm for substitution operation using the recursive approach.
 * 
 * This test verifies that the recursive implementation correctly calculates the edit distance when substitutions are needed
 * to convert one string into another.
 */
void test_edit_distance_substitution_recursive(void);

/**
 * @brief Test the edit distance algorithm for mixed operations using the recursive approach.
 * 
 * This test verifies that the recursive implementation correctly calculates the edit distance when a combination of insertions,
 * deletions, and substitutions are required to convert one string into another.
 */
void test_edit_distance_mixed_operations_recursive(void);

/**
 * @brief Test the edit distance algorithm for null string input using the recursive approach.
 * 
 * This test verifies that the recursive implementation correctly handles the case where one or both of the input strings
 * are null.
 */
void test_edit_distance_null_string_recursive(void);

/**
 * @brief Test the edit distance algorithm for identical strings using the dynamic programming approach.
 * 
 * This test verifies that the dynamic programming implementation correctly returns a distance of 0 when the input strings
 * are identical.
 */
void test_edit_distance_identical_strings_dynamic(void);

/**
 * @brief Test the edit distance algorithm for an empty string using the dynamic programming approach.
 * 
 * This test verifies that the dynamic programming implementation correctly handles the case where one of the strings is empty,
 * and the distance is equal to the length of the non-empty string.
 */
void test_edit_distance_empty_string_dynamic(void);

/**
 * @brief Test the edit distance algorithm for insertion operation using the dynamic programming approach.
 * 
 * This test verifies that the dynamic programming implementation correctly calculates the edit distance when insertions are needed
 * to convert one string into another.
 */
void test_edit_distance_insertion_dynamic(void);

/**
 * @brief Test the edit distance algorithm for deletion operation using the dynamic programming approach.
 * 
 * This test verifies that the dynamic programming implementation correctly calculates the edit distance when deletions are needed
 * to convert one string into another.
 */
void test_edit_distance_deletion_dynamic(void);

/**
 * @brief Test the edit distance algorithm for substitution operation using the dynamic programming approach.
 * 
 * This test verifies that the dynamic programming implementation correctly calculates the edit distance when substitutions are needed
 * to convert one string into another.
 */
void test_edit_distance_substitution_dynamic(void);

/**
 * @brief Test the edit distance algorithm for mixed operations using the dynamic programming approach.
 * 
 * This test verifies that the dynamic programming implementation correctly calculates the edit distance when a combination of insertions,
 * deletions, and substitutions are required to convert one string into another.
 */
void test_edit_distance_mixed_operations_dynamic(void);

/**
 * @brief Test the edit distance algorithm for null string input using the dynamic programming approach.
 * 
 * This test verifies that the dynamic programming implementation correctly handles the case where one or both of the input strings
 * are null.
 */
void test_edit_distance_null_string_dynamic(void);

#endif  // _TEST_EDIT_DISTANCE_H
