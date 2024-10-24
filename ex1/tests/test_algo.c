#include "../src/algo.h"
#include "../../Resources/C/Unity/unity.h"
#include <stdio.h>


int int_cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

// SetUp and TearDown functions (are needed by Unity)
void setUp(void) {}
void tearDown(void) {}

// Test case for merge_sort
void test_merge_sort(void) {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {5, 6, 7, 11, 12, 13};

    merge_sort(arr, n, sizeof(int), int_cmp);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, n);
}

// Test case for sorting an empty array
void test_merge_sort_empty(void) {
    int arr[] = {};
    int n = 0;

    merge_sort(arr, n, sizeof(int), int_cmp);

    // If array is empty, just confirm no segmentation faults or crashes occurred
    TEST_ASSERT_TRUE(1);
}

// Test case for sorting an already sorted array
void test_merge_sort_sorted(void) {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {1, 2, 3, 4, 5, 6};

    merge_sort(arr, n, sizeof(int), int_cmp);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, n);
}

// Test case for sorting a reverse-sorted array
void test_merge_sort_reverse_sorted(void) {
    int arr[] = {6, 5, 4, 3, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {1, 2, 3, 4, 5, 6};

    merge_sort(arr, n, sizeof(int), int_cmp);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, n);
}

// Test case for sorting an array with all identical elements
void test_merge_sort_identical_elements(void) {
    int arr[] = {4, 4, 4, 4, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {4, 4, 4, 4, 4};

    merge_sort(arr, n, sizeof(int), int_cmp);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, n);
}

// Test case for sorting an array with a single element
void test_merge_sort_single_element(void) {
    int arr[] = {42};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {42};

    merge_sort(arr, n, sizeof(int), int_cmp);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, n);
}

// Test case for sorting an array with negative numbers
void test_merge_sort_negative_numbers(void) {
    int arr[] = {-3, -1, -4, -2, -5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {-5, -4, -3, -2, -1};

    merge_sort(arr, n, sizeof(int), int_cmp);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, n);
}


// Test case for quick_sort
void test_quick_sort(void) {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {5, 6, 7, 11, 12, 13};

    quick_sort(arr, n, sizeof(int), int_cmp);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, n);
}

// Test case for sorting an empty array
void test_quick_sort_empty(void) {
    int arr[] = {};
    int n = 0;

    quick_sort(arr, n, sizeof(int), int_cmp);

    // If array is empty, just confirm no segmentation faults or crashes occurred
    TEST_ASSERT_TRUE(1);
}

// Test case for sorting an already sorted array
void test_quick_sort_sorted(void) {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {1, 2, 3, 4, 5, 6};

    quick_sort(arr, n, sizeof(int), int_cmp);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, n);
}

// Test case for sorting a reverse-sorted array
void test_quick_sort_reverse_sorted(void) {
    int arr[] = {6, 5, 4, 3, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {1, 2, 3, 4, 5, 6};

    quick_sort(arr, n, sizeof(int), int_cmp);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, n);
}

// Test case for sorting an array with all identical elements
void test_quick_sort_identical_elements(void) {
    int arr[] = {4, 4, 4, 4, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {4, 4, 4, 4, 4};

    quick_sort(arr, n, sizeof(int), int_cmp);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, n);
}

// Test case for sorting an array with a single element
void test_quick_sort_single_element(void) {
    int arr[] = {42};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {42};

    quick_sort(arr, n, sizeof(int), int_cmp);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, n);
}

// Test case for sorting an array with negative numbers
void test_quick_sort_negative_numbers(void) {
    int arr[] = {-3, -1, -4, -2, -5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {-5, -4, -3, -2, -1};

    quick_sort(arr, n, sizeof(int), int_cmp);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, n);
}

int main(void) {
    UNITY_BEGIN();

    // merge_sort tests

    RUN_TEST(test_merge_sort);
    RUN_TEST(test_merge_sort_empty);
    RUN_TEST(test_merge_sort_sorted);
    RUN_TEST(test_merge_sort_reverse_sorted);
    RUN_TEST(test_merge_sort_identical_elements);
    RUN_TEST(test_merge_sort_single_element);
    RUN_TEST(test_merge_sort_negative_numbers);

    // quick_sort tests

    RUN_TEST(test_quick_sort);
    RUN_TEST(test_quick_sort_empty);
    RUN_TEST(test_quick_sort_sorted);
    RUN_TEST(test_quick_sort_reverse_sorted);
    RUN_TEST(test_quick_sort_identical_elements);
    RUN_TEST(test_quick_sort_single_element);
    RUN_TEST(test_quick_sort_negative_numbers);

    return UNITY_END();
}
