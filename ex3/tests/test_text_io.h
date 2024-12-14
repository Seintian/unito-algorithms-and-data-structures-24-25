/**
 * @file test_io_text.h
 * @brief Unit test header for text_io functions.
 *
 * This header file contains the declarations of the unit test functions for
 * the text_io functions. These tests ensure that the functions related to
 * text file reading, word counting, and word insertion into a hash table
 * are working correctly.
 * 
 * @see text_io.h
 */

#ifndef _TEXT_IO_TEST_H
#define _TEXT_IO_TEST_H

#include "unity.h"
#include "text_io.h"
#include "hashtable.h"


/**
 * @brief Test the `count_words` function with a valid file.
 *
 * This test case checks the behavior of the `count_words` function when
 * provided with a valid file containing text. It ensures that the function
 * correctly counts the number of words in the file.
 */
void test_count_words_valid_file(void);

/**
 * @brief Test the `count_words` function with a null file.
 *
 * This test case checks the behavior of the `count_words` function when
 * provided with a null file pointer. It ensures that the function handles
 * this case gracefully, possibly by returning 0 or an error.
 */
void test_count_words_null_file(void);

/**
 * @brief Test the `read_text` function with a valid file.
 *
 * This test case checks the behavior of the `read_text` function when
 * provided with a valid file containing text. It ensures that the function
 * correctly reads the contents of the file.
 */
void test_read_text_valid_file(void);

/**
 * @brief Test the `read_text` function with a null file.
 *
 * This test case checks the behavior of the `read_text` function when
 * provided with a null file pointer. It ensures that the function handles
 * this case gracefully, possibly by returning an error or null pointer.
 */
void test_read_text_null_file(void);

/**
 * @brief Test the `insert_word` function when inserting an existing word.
 *
 * This test case checks the behavior of the `insert_word` function when
 * attempting to insert a word that already exists in the hash table. It ensures
 * that the function handles this case correctly, possibly by updating the word
 * count or ignoring the insertion.
 */
void test_insert_word_existing_word(void);

/**
 * @brief Test the `insert_word` function when inserting a new word.
 *
 * This test case checks the behavior of the `insert_word` function when
 * inserting a new word into the hash table. It ensures that the function
 * correctly adds the new word and updates the hash table.
 */
void test_insert_word_new_word(void);

#endif // _TEXT_IO_TEST_H
