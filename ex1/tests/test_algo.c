/**
 * @file test_algo.c
 * @brief Unit tests for sorting algorithms using the Unity framework.
 *
 * This source file contains the implementation of test cases to validate
 * the correctness of `merge_sort` and `quick_sort` functions. 
 */

#include "algo.h"
#include "unity.h"
#include <stdio.h>


/**
 * @brief Comparator function for integers.
 *
 * This function is used as a comparison callback for sorting algorithms.
 *
 * @param a Pointer to the first integer.
 * @param b Pointer to the second integer.
 * @return Difference between the two integers.
 */
static int int_cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

// -------------------------- Merge Sort Tests --------------------------

void test_merge_sort(void) {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {5, 6, 7, 11, 12, 13};

    merge_sort(arr, n, sizeof(int), int_cmp);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, n);
}

void test_merge_sort_empty(void) {
    int arr[] = {};
    int n = 0;

    merge_sort(arr, n, sizeof(int), int_cmp);

    // If array is empty, just confirm no segmentation faults or crashes occurred
    TEST_ASSERT_TRUE(1);
}

void test_merge_sort_sorted(void) {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {1, 2, 3, 4, 5, 6};

    merge_sort(arr, n, sizeof(int), int_cmp);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, n);
}

void test_merge_sort_reverse_sorted(void) {
    int arr[] = {6, 5, 4, 3, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {1, 2, 3, 4, 5, 6};

    merge_sort(arr, n, sizeof(int), int_cmp);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, n);
}

void test_merge_sort_identical_elements(void) {
    int arr[] = {4, 4, 4, 4, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {4, 4, 4, 4, 4};

    merge_sort(arr, n, sizeof(int), int_cmp);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, n);
}

void test_merge_sort_single_element(void) {
    int arr[] = {42};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {42};

    merge_sort(arr, n, sizeof(int), int_cmp);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, n);
}

void test_merge_sort_negative_numbers(void) {
    int arr[] = {-3, -1, -4, -2, -5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {-5, -4, -3, -2, -1};

    merge_sort(arr, n, sizeof(int), int_cmp);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, n);
}

// -------------------------- Quick Sort Tests --------------------------

void test_quick_sort(void) {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {5, 6, 7, 11, 12, 13};

    quick_sort(arr, n, sizeof(int), int_cmp);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, n);
}

void test_quick_sort_empty(void) {
    int arr[] = {};
    int n = 0;

    quick_sort(arr, n, sizeof(int), int_cmp);

    // If array is empty, just confirm no segmentation faults or crashes occurred
    TEST_ASSERT_TRUE(1);
}

void test_quick_sort_sorted(void) {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {1, 2, 3, 4, 5, 6};

    quick_sort(arr, n, sizeof(int), int_cmp);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, n);
}

void test_quick_sort_reverse_sorted(void) {
    int arr[] = {6, 5, 4, 3, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {1, 2, 3, 4, 5, 6};

    quick_sort(arr, n, sizeof(int), int_cmp);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, n);
}

void test_quick_sort_identical_elements(void) {
    int arr[] = {4, 4, 4, 4, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {4, 4, 4, 4, 4};

    quick_sort(arr, n, sizeof(int), int_cmp);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, n);
}

void test_quick_sort_single_element(void) {
    int arr[] = {42};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {42};

    quick_sort(arr, n, sizeof(int), int_cmp);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, n);
}

void test_quick_sort_negative_numbers(void) {
    int arr[] = {-3, -1, -4, -2, -5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {-5, -4, -3, -2, -1};

    quick_sort(arr, n, sizeof(int), int_cmp);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, n);
}
