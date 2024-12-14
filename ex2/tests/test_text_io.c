/**
 * @file test_text_io.c
 * @brief Unit tests for the text_io interface functions.
 * 
 * This file contains the implementation of unit tests for the text_io interface functions.
 */

#include "unity.h"
#include "text_io.h"
#include <stdio.h>
#include <stdlib.h>

#define TEST_FILE "test_file.txt"
#define DICTIONARY_FILE "dictionary.txt"
#define CORRECT_FILE "to_correct.txt"

/* Helper function to create a test file with some content */
void create_test_file(const char* filename) {
    FILE* file = fopen(filename, "w");
    TEST_ASSERT_NOT_NULL(file);
    fprintf(file, "Hello world\n");
    fprintf(file, "This is a test file.\n");
    fclose(file);
}

/* Helper function to create a dictionary file */
void create_dictionary_file(const char* filename) {
    FILE* file = fopen(filename, "w");
    TEST_ASSERT_NOT_NULL(file);
    fprintf(file, "apple\n");
    fprintf(file, "banana\n");
    fprintf(file, "cherry\n");
    fclose(file);
}

/* Helper function to create a file to correct */
void create_to_correct_file(const char* filename) {
    FILE* file = fopen(filename, "w");
    TEST_ASSERT_NOT_NULL(file);
    fprintf(file, "I have a aplle and a bananna.\n");
    fclose(file);
}

/* Test count_lines function */
void test_count_lines_valid_file(void) {
    create_test_file(TEST_FILE);
    FILE* file = fopen(TEST_FILE, "r");
    TEST_ASSERT_NOT_NULL(file);
    TEST_ASSERT_EQUAL_INT(2, count_lines(file));
    fclose(file);
}

void test_count_lines_empty_file(void) {
    FILE* file = fopen("empty.txt", "w");
    TEST_ASSERT_NOT_NULL(file);
    fclose(file);
    file = fopen("empty.txt", "r");
    TEST_ASSERT_NOT_NULL(file);
    TEST_ASSERT_EQUAL_INT(0, count_lines(file));
    fclose(file);
}

void test_count_lines_invalid_file(void) {
    FILE* file = fopen("nonexistent.txt", "r");
    TEST_ASSERT_NULL(file);
    TEST_ASSERT_EQUAL_INT(-1, count_lines(file));
}

/* Test count_words function */
void test_count_words_valid_file(void) {
    create_test_file(TEST_FILE);
    FILE* file = fopen(TEST_FILE, "r");
    TEST_ASSERT_NOT_NULL(file);
    TEST_ASSERT_EQUAL_INT(6, count_words(file));  // "Hello", "world", "This", "is", "a", "test"
    fclose(file);
}

void test_count_words_empty_file(void) {
    FILE* file = fopen("empty.txt", "w");
    TEST_ASSERT_NOT_NULL(file);
    fclose(file);
    file = fopen("empty.txt", "r");
    TEST_ASSERT_NOT_NULL(file);
    TEST_ASSERT_EQUAL_INT(0, count_words(file));
    fclose(file);
}

void test_count_words_invalid_file(void) {
    FILE* file = fopen("nonexistent.txt", "r");
    TEST_ASSERT_NULL(file);
    TEST_ASSERT_EQUAL_INT(-1, count_words(file));
}

/* Test read_dictionary function */
void test_read_dictionary_valid_file(void) {
    create_dictionary_file(DICTIONARY_FILE);
    FILE* file = fopen(DICTIONARY_FILE, "r");
    TEST_ASSERT_NOT_NULL(file);
    char** dictionary = NULL;
    int count = read_dictionary(file, &dictionary);
    TEST_ASSERT_EQUAL_INT(3, count);
    TEST_ASSERT_NOT_NULL(dictionary);
    TEST_ASSERT_EQUAL_STRING("apple", dictionary[0]);
    TEST_ASSERT_EQUAL_STRING("banana", dictionary[1]);
    TEST_ASSERT_EQUAL_STRING("cherry", dictionary[2]);
    fclose(file);
    free(dictionary);
}

void test_read_dictionary_invalid_file(void) {
    FILE* file = fopen("nonexistent.txt", "r");
    TEST_ASSERT_NULL(file);
    char** dictionary = NULL;
    int count = read_dictionary(file, &dictionary);
    TEST_ASSERT_EQUAL_INT(-1, count);
}

/* Test read_to_correct function */
void test_read_to_correct_valid_file(void) {
    create_to_correct_file(CORRECT_FILE);
    FILE* file = fopen(CORRECT_FILE, "r");
    TEST_ASSERT_NOT_NULL(file);
    char** to_correct = NULL;
    int count = read_to_correct(file, &to_correct);
    TEST_ASSERT_EQUAL_INT(7, count);  // "I", "have", "a", "aplle", "and", "a", "bananna"
    TEST_ASSERT_NOT_NULL(to_correct);
    TEST_ASSERT_EQUAL_STRING("I", to_correct[0]);
    TEST_ASSERT_EQUAL_STRING("have", to_correct[1]);
    TEST_ASSERT_EQUAL_STRING("a", to_correct[2]);
    TEST_ASSERT_EQUAL_STRING("aplle", to_correct[3]);
    TEST_ASSERT_EQUAL_STRING("and", to_correct[4]);
    TEST_ASSERT_EQUAL_STRING("a", to_correct[5]);
    TEST_ASSERT_EQUAL_STRING("bananna", to_correct[6]);
    fclose(file);
    free(to_correct);
}

void test_read_to_correct_invalid_file(void) {
    FILE* file = fopen("nonexistent.txt", "r");
    TEST_ASSERT_NULL(file);
    char** to_correct = NULL;
    int count = read_to_correct(file, &to_correct);
    TEST_ASSERT_EQUAL_INT(-1, count);
}

/* Cleanup test files */
void cleanup_test_files(void) {
    remove(TEST_FILE);
    remove(DICTIONARY_FILE);
    remove(CORRECT_FILE);
    remove("empty.txt");
}
