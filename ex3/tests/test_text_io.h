/**
 * @file test_io_text.h
 * @brief Unit test header for text_io functions.
 */

#ifndef _TEXT_IO_TEST_H
#define _TEXT_IO_TEST_H

#include "unity.h"
#include "text_io.h"
#include "hashtable.h"

// Function declarations for test cases
void test_count_words_valid_file(void);
void test_count_words_null_file(void);
void test_read_text_valid_file(void);
void test_read_text_null_file(void);
void test_insert_word_existing_word(void);
void test_insert_word_new_word(void);

#endif // _TEXT_IO_TEST_H
