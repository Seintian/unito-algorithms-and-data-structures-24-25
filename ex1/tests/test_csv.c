/**
 * @file test_csv.c
 * @brief Unit tests for CSV operations such as comparing fields, counting lines, and reading/writing records.
 * 
 * This file contains the implementation of unit tests for the CSV utility functions.
 */

#include "test_csv.h"
#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock data for testing
static Record record1 = {1, "Alice", 10, 5.5}; ///< Mock record 1 for testing.
static Record record2 = {2, "Bob", 20, 7.8};   ///< Mock record 2 for testing.
static Record record3 = {3, "Alice", 15, 9.9}; ///< Mock record 3 for testing.
static Record record4 = {4, "Charlie", 30, 3.2}; ///< Mock record 4 for testing.

/**
 * @brief Utility function to create a temporary file for testing purposes.
 * 
 * This function creates a temporary file, writes the provided content to it, and returns the file pointer.
 * The file is created using the `tmpfile` function and its content is written using `fputs`.
 * The file pointer is rewound before returning it.
 * 
 * @param content The content to write to the temporary file.
 * 
 * @return FILE* A pointer to the created temporary file.
 * 
 * @note The function exits the program if the temporary file cannot be created.
 */
static FILE* create_temp_file(const char* content) {
    FILE* temp = tmpfile();
    if (temp == NULL) {
        fprintf(stderr, "Unable to create temporary file\n");
        exit(EXIT_FAILURE);
    }

    fputs(content, temp);
    rewind(temp);

    return temp;
}

/**
 * @brief Unit test for comparing the first field of two records.
 * 
 * This test validates the behavior of the `compare_field1` function. It checks:
 * - If `record1` is less than `record2` based on the first field.
 * - If `record1` is equal to `record3` based on the first field.
 * - If `record2` is greater than `record1` based on the first field.
 */
void test_compare_field1() {
    TEST_ASSERT_TRUE(compare_field1(&record1, &record2) < 0);
    TEST_ASSERT_TRUE(compare_field1(&record1, &record3) == 0);
    TEST_ASSERT_TRUE(compare_field1(&record2, &record1) > 0);
}

/**
 * @brief Unit test for comparing the second field of two records.
 * 
 * This test validates the behavior of the `compare_field2` function. It checks:
 * - If `record1` is less than `record2` based on the second field.
 * - If `record3` is equal to itself based on the second field.
 * - If `record4` is greater than `record1` based on the second field.
 */
void test_compare_field2() {
    TEST_ASSERT_TRUE(compare_field2(&record1, &record2) < 0);
    TEST_ASSERT_TRUE(compare_field2(&record3, &record3) == 0);
    TEST_ASSERT_TRUE(compare_field2(&record4, &record1) > 0);
}

/**
 * @brief Unit test for comparing the third field of two records.
 * 
 * This test validates the behavior of the `compare_field3` function. It checks:
 * - If `record1` is less than `record2` based on the third field.
 * - If `record3` is equal to itself based on the third field.
 * - If `record2` is greater than `record1` based on the third field.
 */
void test_compare_field3() {
    TEST_ASSERT_TRUE(compare_field3(&record1, &record2) < 0);
    TEST_ASSERT_TRUE(compare_field3(&record3, &record3) == 0);
    TEST_ASSERT_TRUE(compare_field3(&record2, &record1) > 0);
}

/**
 * @brief Unit test for counting the number of lines in a file.
 * 
 * This test validates the behavior of the `count_lines` function. It checks:
 * - If the function correctly counts the lines in a non-empty file.
 * - If the function returns 0 for an empty file.
 * 
 * @note A temporary file is created for each test case.
 */
void test_count_lines() {
    FILE* temp_file = create_temp_file("Line1\nLine2\nLine3\nLine4\nLine5\n");
    TEST_ASSERT_EQUAL(5, count_lines(temp_file));
    fclose(temp_file);

    temp_file = create_temp_file("");
    TEST_ASSERT_EQUAL(0, count_lines(temp_file));
    fclose(temp_file);
}

/**
 * @brief Unit test for reading records from a file.
 * 
 * This test validates the behavior of the `read_records` function. It checks:
 * - If the function correctly reads records from a file with valid data.
 * - If the function returns 0 when reading from an empty file.
 * 
 * @note A temporary file is created for each test case.
 */
void test_read_records() {
    // Test with valid data
    FILE* temp_file = create_temp_file("1,Alice,10,5.5\n2,Bob,20,7.8\n3,Charlie,30,9.9\n");
    Record records[3];
    size_t n = read_records(temp_file, records, 3);
    TEST_ASSERT_EQUAL(3, n);
    TEST_ASSERT_EQUAL_STRING("Alice", records[0].field1);
    TEST_ASSERT_EQUAL_STRING("Bob", records[1].field1);
    TEST_ASSERT_EQUAL_STRING("Charlie", records[2].field1);

    free(records[0].field1);
    free(records[1].field1);
    free(records[2].field1);
    
    fclose(temp_file);

    // Test with empty file
    temp_file = create_temp_file("");
    n = read_records(temp_file, records, 3);
    TEST_ASSERT_EQUAL(0, n);

    fclose(temp_file);
}

/**
 * @brief Unit test for writing records to a file.
 * 
 * This test validates the behavior of the `write_records` function. It checks:
 * - If the function correctly writes records to a file.
 * - If the written records match the expected format.
 * 
 * @note A temporary file is created for each test case.
 */
void test_write_records() {
    Record records[3] = {
        {1, "Alice", 10, 5.5},
        {2, "Bob", 20, 7.8},
        {3, "Charlie", 30, 9.9}
    };

    FILE* temp_file = tmpfile();
    if (temp_file == NULL) {
        fprintf(stderr, "Unable to create temporary file\n");
        exit(EXIT_FAILURE);
    }

    size_t n = write_records(temp_file, records, 3);
    TEST_ASSERT_EQUAL(3, n);

    rewind(temp_file);

    char buffer[MAX_LINE_SIZE];
    char expected[MAX_LINE_SIZE];

    fgets(buffer, sizeof(buffer), temp_file);
    sprintf(expected, recordWriteFmt, records[0].id, records[0].field1, records[0].field2, records[0].field3);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);

    fgets(buffer, sizeof(buffer), temp_file);
    sprintf(expected, recordWriteFmt, records[1].id, records[1].field1, records[1].field2, records[1].field3);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);

    fgets(buffer, sizeof(buffer), temp_file);
    sprintf(expected, recordWriteFmt, records[2].id, records[2].field1, records[2].field2, records[2].field3);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);

    fclose(temp_file);
}
