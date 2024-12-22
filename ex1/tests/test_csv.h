/**
 * @file test_csv.h
 * @brief Unit test declarations for CSV-related functionality.
 *
 * This header file declares test cases for functions related to CSV
 * operations. The tests are implemented using the Unity framework to
 * ensure correctness and robustness of the CSV utility functions.
 * 
 * @see csv.h
 */

#ifndef _TEST_CSV_H
#define _TEST_CSV_H

#include "csv.h"
#include "unity.h"


/**
 * @brief Test case for the `compare_field1` function.
 *
 * Verifies that `compare_field1` correctly compares the first field
 * of two CSV records.
 */
void test_compare_field1();

/**
 * @brief Test case for the `compare_field2` function.
 *
 * Verifies that `compare_field2` correctly compares the second field
 * of two CSV records.
 */
void test_compare_field2();

/**
 * @brief Test case for the `compare_field3` function.
 *
 * Verifies that `compare_field3` correctly compares the third field
 * of two CSV records.
 */
void test_compare_field3();

/**
 * @brief Test case for the `count_lines` function.
 *
 * Ensures that `count_lines` accurately counts the number of lines
 * in a given CSV file.
 */
void test_count_lines();

/**
 * @brief Test case for the `read_records` function.
 *
 * Validates that `read_records` correctly reads and parses records
 * from a CSV file into the appropriate data structure.
 */
void test_read_records();

/**
 * @brief Test case for the `write_records` function.
 *
 * Confirms that `write_records` correctly writes data records into
 * a CSV file in the expected format.
 */
void test_write_records();

#endif // _TEST_CSV_H
