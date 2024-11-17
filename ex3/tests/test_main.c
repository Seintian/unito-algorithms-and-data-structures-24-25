/**
 * @file test_main.c
 * @brief Entry point for the test suite. Contains tests for hash tables and prime numbers.
 */

#include "unity.h"
#include "test_hashtable.h"
#include "test_prime.h"
#include "test_text_io.h"


int main() {
    UNITY_BEGIN();

    // hash table tests: basic operations
    RUN_TEST(test_hash_table_create);
    RUN_TEST(test_hash_table_put_and_get);
    RUN_TEST(test_hash_table_resized);
    RUN_TEST(test_hash_table_update_existing_key);
    RUN_TEST(test_hash_table_contains_key);
    RUN_TEST(test_hash_table_remove);
    RUN_TEST(test_hash_table_keyset);
    RUN_TEST(test_hash_table_values);
    RUN_TEST(test_hash_table_clear);
    RUN_TEST(test_hash_table_load_factor);
    RUN_TEST(test_hash_table_replace);
    RUN_TEST(test_hash_table_map);
    RUN_TEST(test_hash_table_equals);
    RUN_TEST(test_hash_table_copy);
    RUN_TEST(test_hash_table_merge);

    // prime number tests

    RUN_TEST(test_is_prime);
    RUN_TEST(test_next_prime);

    // text_io tests

    RUN_TEST(test_count_words_valid_file);
    RUN_TEST(test_count_words_null_file);
    RUN_TEST(test_read_text_valid_file);
    RUN_TEST(test_read_text_null_file);
    RUN_TEST(test_insert_word_existing_word);
    RUN_TEST(test_insert_word_new_word);

    return UNITY_END();
}