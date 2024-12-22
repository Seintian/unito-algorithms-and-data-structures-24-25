/**
 * @file test_algo.h
 * @brief Unit test declarations for sorting algorithms using the Unity framework.
 *
 * This header file contains declarations of test cases for verifying the 
 * functionality of sorting algorithms implemented in `algo.h`. The tests 
 * cover various scenarios to ensure the algorithms handle edge cases and 
 * common use cases correctly.
 * 
 * @see algo.h
 */

#ifndef _TEST_ALGO_H
#define _TEST_ALGO_H

#include "algo.h"
#include "unity.h"

/**
 * @brief Test case for merge_sort on a general unsorted array.
 *
 * This test verifies that the merge_sort function correctly sorts an 
 * unsorted array of integers.
 */
void test_merge_sort(void);

/**
 * @brief Test case for merge_sort on an empty array.
 *
 * This test ensures that merge_sort handles an empty array gracefully 
 * without errors and leaves it unchanged.
 */
void test_merge_sort_empty(void);

/**
 * @brief Test case for merge_sort on an already sorted array.
 *
 * This test checks that merge_sort does not alter an array that is 
 * already sorted.
 */
void test_merge_sort_sorted(void);

/**
 * @brief Test case for merge_sort on a reverse-sorted array.
 *
 * This test ensures that merge_sort can correctly sort an array sorted 
 * in descending order into ascending order.
 */
void test_merge_sort_reverse_sorted(void);

/**
 * @brief Test case for merge_sort on an array with all identical elements.
 *
 * This test verifies that merge_sort correctly handles an array where 
 * all elements are the same, leaving it unchanged.
 */
void test_merge_sort_identical_elements(void);

/**
 * @brief Test case for merge_sort on an array with a single element.
 *
 * This test ensures that merge_sort correctly handles an array with 
 * only one element, leaving it unchanged.
 */
void test_merge_sort_single_element(void);

/**
 * @brief Test case for merge_sort on an array with negative numbers.
 *
 * This test verifies that merge_sort can correctly sort an array 
 * containing negative integers.
 */
void test_merge_sort_negative_numbers(void);

/**
 * @brief Test case for quick_sort on a general unsorted array.
 *
 * This test verifies that the quick_sort function correctly sorts an 
 * unsorted array of integers.
 */
void test_quick_sort(void);

/**
 * @brief Test case for quick_sort on an empty array.
 *
 * This test ensures that quick_sort handles an empty array gracefully 
 * without errors and leaves it unchanged.
 */
void test_quick_sort_empty(void);

/**
 * @brief Test case for quick_sort on an already sorted array.
 *
 * This test checks that quick_sort does not alter an array that is 
 * already sorted.
 */
void test_quick_sort_sorted(void);

/**
 * @brief Test case for quick_sort on a reverse-sorted array.
 *
 * This test ensures that quick_sort can correctly sort an array sorted 
 * in descending order into ascending order.
 */
void test_quick_sort_reverse_sorted(void);

/**
 * @brief Test case for quick_sort on an array with all identical elements.
 *
 * This test verifies that quick_sort correctly handles an array where 
 * all elements are the same, leaving it unchanged.
 */
void test_quick_sort_identical_elements(void);

/**
 * @brief Test case for quick_sort on an array with a single element.
 *
 * This test ensures that quick_sort correctly handles an array with 
 * only one element, leaving it unchanged.
 */
void test_quick_sort_single_element(void);

/**
 * @brief Test case for quick_sort on an array with negative numbers.
 *
 * This test verifies that quick_sort can correctly sort an array 
 * containing negative integers.
 */
void test_quick_sort_negative_numbers(void);

#endif  // _TEST_ALGO_H
