#include "test_csv.h"
#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Mock data for testing
Record record1 = {1, "Alice", 10, 5.5};
Record record2 = {2, "Bob", 20, 7.8};
Record record3 = {3, "Alice", 15, 9.9};
Record record4 = {4, "Charlie", 30, 3.2};

// Utility function to create a temporary file for testing
FILE* create_temp_file(const char* content) {
    FILE* temp = tmpfile();
    if (temp == NULL) {
        fprintf(stderr, "Unable to create temporary file\n");
        exit(EXIT_FAILURE);
    }

    fputs(content, temp);
    rewind(temp);

    return temp;
}

void test_compare_field1() {
    TEST_ASSERT_TRUE(compare_field1(&record1, &record2) < 0);
    TEST_ASSERT_TRUE(compare_field1(&record1, &record3) == 0);
    TEST_ASSERT_TRUE(compare_field1(&record2, &record1) > 0);
}

void test_compare_field2() {
    TEST_ASSERT_TRUE(compare_field2(&record1, &record2) < 0);
    TEST_ASSERT_TRUE(compare_field2(&record3, &record3) == 0);
    TEST_ASSERT_TRUE(compare_field2(&record4, &record1) > 0);
}

void test_compare_field3() {
    TEST_ASSERT_TRUE(compare_field3(&record1, &record2) < 0);
    TEST_ASSERT_TRUE(compare_field3(&record3, &record3) == 0);
    TEST_ASSERT_TRUE(compare_field3(&record2, &record1) > 0);
}

void test_count_lines() {
    FILE* temp_file = create_temp_file("Line1\nLine2\nLine3\nLine4\nLine5\n");
    TEST_ASSERT_EQUAL(5, count_lines(temp_file));
    fclose(temp_file);

    temp_file = create_temp_file("");
    TEST_ASSERT_EQUAL(0, count_lines(temp_file));
    fclose(temp_file);
}

void test_read_records() {
    // Test with valid data
    FILE* temp_file = create_temp_file("1,Alice,10,5.5\n2,Bob,20,7.8\n3,Charlie,30,9.9\n");
    Record records[3];
    size_t n = read_records(temp_file, records, 3);
    TEST_ASSERT_EQUAL(3, n);
    TEST_ASSERT_EQUAL_STRING("Alice", records[0].field1);
    TEST_ASSERT_EQUAL_STRING("Bob", records[1].field1);
    TEST_ASSERT_EQUAL_STRING("Charlie", records[2].field1);
    
    fclose(temp_file);

    // Test with empty file
    temp_file = create_temp_file("");
    n = read_records(temp_file, records, 3);
    TEST_ASSERT_EQUAL(0, n);

    fclose(temp_file);
}

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
