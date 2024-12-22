/**
 * @file test_main.c
 * @brief Entry point for the unit tests.
 * 
 * This file contains the main function that runs the unit tests for the 
 * edit_distance algorithm in both recursive and dynamic programming versions.
 * It uses the Unity testing framework to run the test cases for different 
 * scenarios of the edit distance algorithm.
 * 
 * The tests cover a variety of cases, including identical strings, empty strings,
 * insertions, deletions, substitutions, mixed operations, and null string inputs.
 * The tests are organized by the algorithm version: recursive and dynamic.
 * 
 * @note The `setUp` and `tearDown` functions are required by Unity but are empty in this file.
 * 
 * @see test_edit_distance.h
 * @see test_text_io.h
 * @see Unity
 */

#include "unity.h"
#include "test_edit_distance.h"


/**
 * @brief Set up the testing environment.
 * 
 * This function is called before each test case to set up any necessary 
 * resources or configurations. It is part of the Unity framework's test 
 * lifecycle.
 * 
 * This function is currently a placeholder and can be customized to 
 * initialize any required state before running the tests.
 */
void setUp(void) {
    // set stuff up here
}

/**
 * @brief Tear down the testing environment.
 * 
 * This function is called after each test case to clean up any resources 
 * or reset configurations. It is part of the Unity framework's test 
 * lifecycle.
 * 
 * This function is currently a placeholder and can be customized to 
 * release any resources or perform any necessary cleanup after each test.
 */
void tearDown(void) {
    // clean stuff up here
}

/**
 * @brief Main entry point for running the unit tests.
 * 
 * This function initializes the Unity test framework and runs a series of 
 * unit tests for the edit distance algorithm. It includes tests for both 
 * the recursive and dynamic programming implementations of the algorithm.
 * 
 * The tests are grouped by the type of operation they test:
 * - Recursive version: Tests for identical strings, empty strings, insertions, deletions, substitutions, mixed operations, and null strings.
 * - Dynamic programming version: Tests for identical strings, empty strings, insertions, deletions, substitutions, mixed operations, and null strings.
 * 
 * @return An integer indicating the result of the test run. Returns 0 if all tests pass, 
 *         or a non-zero value if any test fails.
 */
int main(void) {
    UNITY_BEGIN();

    // Run tests for recursive edit_distance
    RUN_TEST(test_edit_distance_identical_strings_recursive);
    RUN_TEST(test_edit_distance_empty_string_recursive);
    RUN_TEST(test_edit_distance_insertion_recursive);
    RUN_TEST(test_edit_distance_deletion_recursive);
    RUN_TEST(test_edit_distance_substitution_recursive);
    RUN_TEST(test_edit_distance_mixed_operations_recursive);
    RUN_TEST(test_edit_distance_null_string_recursive);

    // Run tests for dynamic programming edit_distance_dyn
    RUN_TEST(test_edit_distance_identical_strings_dynamic);
    RUN_TEST(test_edit_distance_empty_string_dynamic);
    RUN_TEST(test_edit_distance_insertion_dynamic);
    RUN_TEST(test_edit_distance_deletion_dynamic);
    RUN_TEST(test_edit_distance_substitution_dynamic);
    RUN_TEST(test_edit_distance_mixed_operations_dynamic);
    RUN_TEST(test_edit_distance_null_string_dynamic);

    return UNITY_END();
}
