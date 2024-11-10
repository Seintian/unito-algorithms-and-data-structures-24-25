#ifndef _TEST_ALGO_H
#define _TEST_ALGO_H

#include "algo.h"
#include "unity.h"


// Test case for merge_sort
void test_merge_sort(void);

// Test case for sorting an empty array
void test_merge_sort_empty(void);

// Test case for sorting an already sorted array
void test_merge_sort_sorted(void);

// Test case for sorting a reverse-sorted array
void test_merge_sort_reverse_sorted(void);

// Test case for sorting an array with all identical elements
void test_merge_sort_identical_elements(void);

// Test case for sorting an array with a single element
void test_merge_sort_single_element(void);

// Test case for sorting an array with negative numbers
void test_merge_sort_negative_numbers(void);


// Test case for quick_sort
void test_quick_sort(void);

// Test case for sorting an empty array
void test_quick_sort_empty(void);

// Test case for sorting an already sorted array
void test_quick_sort_sorted(void);

// Test case for sorting a reverse-sorted array
void test_quick_sort_reverse_sorted(void);

// Test case for sorting an array with all identical elements
void test_quick_sort_identical_elements(void);

// Test case for sorting an array with a single element
void test_quick_sort_single_element(void);

// Test case for sorting an array with negative numbers
void test_quick_sort_negative_numbers(void);

#endif  // _TEST_ALGO_H