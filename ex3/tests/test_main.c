/**
 * @file test_main.c
 * @brief Entry point for the test suite. Contains tests for hash tables and prime numbers.
 *
 * This file serves as the main entry point for the unit test suite. It runs the test cases for various
 * modules, including hash tables, prime number operations, and text I/O operations.
 * 
 * The test cases are organized into groups based on their functionality, and each test case is run using
 * the Unity framework's test runner functions.
 *
 * The test suite includes tests for:
 * - Hash table operations
 * - Prime number functions
 * - Text I/O functions
 *
 * @note The `setUp` and `tearDown` functions are required by Unity but are empty in this file.
 * 
 * @see test_hashtable.h
 * @see test_prime.h
 * @see test_text_io.h
 * @see Unity
 */

#include "unity.h"
#include "test_hashtable.h"
#include "test_prime.h"
#include "test_text_io.h"

/**
 * @brief Main entry point for the test suite.
 *
 * This function initializes the Unity test framework, runs all the defined test cases for the hash table,
 * prime numbers, and text I/O modules, and returns the final test result.
 *
 * The test cases for the hash table module cover basic operations such as creating a table, inserting,
 * updating, removing keys, and checking the load factor, among others.
 *
 * The prime number module tests the functionality of determining whether a number is prime and finding the
 * next prime number.
 *
 * The text I/O module tests functions related to counting words in a file, reading text, and inserting words
 * into a hash table.
 *
 * @return The result of running the test suite, which is 0 if all tests pass and a non-zero value if any test fails.
 */
int main() {
    UNITY_BEGIN();

    // hash table tests
    RUN_TEST(test_hash_table_create); ///< Test for creating a hash table
    RUN_TEST(test_hash_table_put_and_get); ///< Test for inserting and retrieving values from the hash table
    RUN_TEST(test_hash_table_resized); ///< Test for resizing the hash table
    RUN_TEST(test_hash_table_update_existing_key); ///< Test for updating an existing key in the hash table
    RUN_TEST(test_hash_table_contains_key); ///< Test for checking if a key exists in the hash table
    RUN_TEST(test_hash_table_remove); ///< Test for removing a key from the hash table
    RUN_TEST(test_hash_table_keyset); ///< Test for retrieving the set of keys in the hash table
    RUN_TEST(test_hash_table_values); ///< Test for retrieving the values associated with keys in the hash table
    RUN_TEST(test_hash_table_clear); ///< Test for clearing all entries in the hash table
    RUN_TEST(test_hash_table_load_factor); ///< Test for checking the load factor of the hash table
    RUN_TEST(test_hash_table_replace); ///< Test for replacing an existing value for a key in the hash table
    RUN_TEST(test_hash_table_map); ///< Test for applying a function to all elements in the hash table
    RUN_TEST(test_hash_table_equals); ///< Test for checking equality of two hash tables
    RUN_TEST(test_hash_table_copy); ///< Test for copying a hash table
    RUN_TEST(test_hash_table_merge); ///< Test for merging two hash tables

    // prime number tests
    RUN_TEST(test_is_prime); ///< Test for checking if a number is prime
    RUN_TEST(test_next_prime); ///< Test for finding the next prime number

    // text_io tests
    RUN_TEST(test_count_words_valid_file); ///< Test for counting words in a valid file
    RUN_TEST(test_count_words_null_file); ///< Test for counting words with a NULL file pointer
    RUN_TEST(test_read_text_valid_file); ///< Test for reading text from a valid file
    RUN_TEST(test_read_text_null_file); ///< Test for reading text with a NULL file pointer
    RUN_TEST(test_insert_word_existing_word); ///< Test for inserting an existing word into the hash table
    RUN_TEST(test_insert_word_new_word); ///< Test for inserting a new word into the hash table

    return UNITY_END();
}
