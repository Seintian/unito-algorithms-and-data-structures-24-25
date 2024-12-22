/**
 * @file test_main.c
 * @brief Main entry point for running unit tests on sorting algorithms and CSV operations.
 * 
 * This file serves as the entry point for running unit tests using the Unity test framework.
 * It includes tests for sorting algorithms (merge sort and quick sort) and CSV operations such as comparing fields,
 * counting lines, and reading/writing records. Each test is run using the `RUN_TEST` macro provided by Unity.
 * 
 * @note The `setUp` and `tearDown` functions are required by Unity but are empty in this file.
 * 
 * @see test_algo.h
 * @see test_csv.h
 * @see Unity
 */

#include "test_algo.h"
#include "test_csv.h"
#include "unity.h"

/**
 * @brief Set up the test environment.
 * 
 * This function is called before each test is executed. It is a required function by the Unity test framework,
 * but it is empty in this case as no setup is needed.
 */
void setUp(void) {}

/**
 * @brief Tear down the test environment.
 * 
 * This function is called after each test is executed. It is a required function by the Unity test framework,
 * but it is empty in this case as no teardown is needed.
 */
void tearDown(void) {}

/**
 * @brief Main entry point for running unit tests.
 * 
 * This function initializes the Unity test framework, runs the various unit tests for sorting algorithms (merge sort,
 * quick sort) and CSV operations, and then returns the test results.
 * 
 * It includes the following test groups:
 * - Merge Sort tests: Various scenarios for merge sort, including empty, sorted, reverse sorted, identical elements,
 *   single element, and negative numbers.
 * - Quick Sort tests: Various scenarios for quick sort, including empty, sorted, reverse sorted, identical elements,
 *   single element, and negative numbers.
 * - CSV tests: Tests for comparing fields, counting lines, and reading/writing records from CSV-like data.
 * 
 * @return int The result of the Unity test framework, indicating whether all tests passed or failed.
 */
int main(void) {
    UNITY_BEGIN(); ///< Initialize Unity test framework.

    // Merge Sort tests
    RUN_TEST(test_merge_sort); ///< Test for merge sort with general data.
    RUN_TEST(test_merge_sort_empty); ///< Test for merge sort with an empty array.
    RUN_TEST(test_merge_sort_sorted); ///< Test for merge sort with already sorted data.
    RUN_TEST(test_merge_sort_reverse_sorted); ///< Test for merge sort with reverse sorted data.
    RUN_TEST(test_merge_sort_identical_elements); ///< Test for merge sort with identical elements.
    RUN_TEST(test_merge_sort_single_element); ///< Test for merge sort with a single element.
    RUN_TEST(test_merge_sort_negative_numbers); ///< Test for merge sort with negative numbers.

    // Quick Sort tests
    RUN_TEST(test_quick_sort); ///< Test for quick sort with general data.
    RUN_TEST(test_quick_sort_empty); ///< Test for quick sort with an empty array.
    RUN_TEST(test_quick_sort_sorted); ///< Test for quick sort with already sorted data.
    RUN_TEST(test_quick_sort_reverse_sorted); ///< Test for quick sort with reverse sorted data.
    RUN_TEST(test_quick_sort_identical_elements); ///< Test for quick sort with identical elements.
    RUN_TEST(test_quick_sort_single_element); ///< Test for quick sort with a single element.
    RUN_TEST(test_quick_sort_negative_numbers); ///< Test for quick sort with negative numbers.

    // CSV tests
    RUN_TEST(test_compare_field1); ///< Test for comparing the first field of records in a CSV.
    RUN_TEST(test_compare_field2); ///< Test for comparing the second field of records in a CSV.
    RUN_TEST(test_compare_field3); ///< Test for comparing the third field of records in a CSV.
    RUN_TEST(test_count_lines); ///< Test for counting the number of lines in a CSV file.
    RUN_TEST(test_read_records); ///< Test for reading records from a CSV file.
    RUN_TEST(test_write_records); ///< Test for writing records to a CSV file.

    return UNITY_END(); ///< Finalize Unity test framework and return the result.
}
