/**
 * @file test_text_io.c
 * @brief Unit tests for text_io functions using Unity framework.
 *
 * This file contains the implementation of unit tests for the text_io functions.
 */

#include "test_text_io.h"
#include <stdio.h>


/**
 * @brief Hash function for strings.
 *
 * This function computes a hash value for a given string using the djb2 algorithm.
 * It is used for testing the hash table functionality with string keys.
 *
 * @param key Pointer to the string to hash.
 * @return The hash value of the string.
 */
static unsigned long string_hash(const void* key) {
    const char* str = (const char*)key;
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash;
}

/**
 * @brief Comparison function for strings.
 *
 * This function compares two strings and is used for testing the hash table
 * functionality with string keys.
 *
 * @param a Pointer to the first string.
 * @param b Pointer to the second string.
 * @return 0 if the strings are equal, a negative value if the first string is less,
 *         or a positive value if the first string is greater.
 */
static int string_compare(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

/**
 * @brief Inserts a word into the hash table.
 *
 * This function inserts a word into the hash table. If the word is already in the hash table,
 * the frequency of the word is incremented. If the word is not in the hash table, it is added
 * with a frequency of 1.
 *
 * @param table Pointer to the hash table.
 * @param word The word to insert.
 * @return 0 if successful, -1 if an error occurs.
 */
static int insert_word(HashTable* table, const char* word) {
    if (table == NULL || word == NULL)
        return -1;

    int* freq = (int*) hash_table_get(table, word);
    if (freq)
        (*freq)++;

    else {
        if (hash_table_contains_key(table, word))
            return -1;

        const char* new_word = strdup(word);
        if (!new_word)
            return -1;

        int* new_freq = (int*) malloc(sizeof(int));
        if (!new_freq)
            return -1;

        *new_freq = 1;
        hash_table_put(table, new_word, new_freq);
    }

    return 0;
}

/**
 * @brief Test case for count_words with a valid file.
 *
 * This test case checks the behavior of the `count_words` function when
 * provided with a valid file containing text. It ensures that the function
 * correctly counts the number of words in the file.
 */
void test_count_words_valid_file(void) {
    FILE* test_fp = tmpfile();
    if (!test_fp)
        return;

    fputs("Hello world! This is a test.", test_fp);
    fseek(test_fp, 0, SEEK_SET);

    int word_count = count_words(test_fp);
    TEST_ASSERT_EQUAL_INT(6, word_count);

    fclose(test_fp);
}

/**
 * @brief Test case for count_words with a NULL file pointer.
 *
 * This test case checks the behavior of the `count_words` function when
 * provided with a NULL file pointer. It ensures that the function handles
 * this case gracefully, possibly by returning an error or a default value.
 */
void test_count_words_null_file(void) {
    int word_count = count_words(NULL);
    TEST_ASSERT_EQUAL_INT(-1, word_count);
}

/**
 * @brief Test case for read_text with a valid file.
 *
 * This test case checks the behavior of the `read_text` function when
 * provided with a valid file containing text. It ensures that the function
 * correctly reads the contents of the file and updates the hash table
 * with the word frequencies.
 */
void test_read_text_valid_file(void) {
    FILE* test_fp = tmpfile();
    if (!test_fp)
        return;

    fputs("Hello world! Hello test.", test_fp);
    fseek(test_fp, 0, SEEK_SET);

    HashTable* table = hash_table_create(string_compare, string_hash);
    int result = read_text(test_fp, &table);
    TEST_ASSERT_EQUAL_INT(0, result);

    const int* freq_hello = (int*) hash_table_get(table, "Hello");
    const int* freq_world = (int*) hash_table_get(table, "world");
    const int* freq_test = (int*) hash_table_get(table, "test");

    TEST_ASSERT_NOT_NULL(freq_hello);
    TEST_ASSERT_NOT_NULL(freq_world);
    TEST_ASSERT_NOT_NULL(freq_test);
    TEST_ASSERT_EQUAL_INT(2, *freq_hello);
    TEST_ASSERT_EQUAL_INT(1, *freq_world);
    TEST_ASSERT_EQUAL_INT(1, *freq_test);

    free((void*) freq_hello);
    free((void*) freq_world);
    free((void*) freq_test);

    void** keys = hash_table_keyset(table);
    for (int i = 0; i < hash_table_size(table); i++)
        free(keys[i]);

    free(keys);

    hash_table_free(table);
    fclose(test_fp);
}

/**
 * @brief Test case for read_text with a NULL file pointer.
 *
 * This test case checks the behavior of the `read_text` function when
 * provided with a NULL file pointer. It ensures that the function handles
 * this case gracefully, possibly by returning an error or null pointer.
 */
void test_read_text_null_file(void) {
    HashTable* table = hash_table_create(string_compare, string_hash);
    int result = read_text(NULL, &table);
    TEST_ASSERT_EQUAL_INT(-1, result);

    hash_table_free(table);
}

/**
 * @brief Test case for inserting an existing word into the hash table.
 *
 * This test case checks the behavior of the `insert_word` function when
 * attempting to insert a word that already exists in the hash table. It ensures
 * that the function correctly increments the word's frequency.
 */
void test_insert_word_existing_word(void) {
    HashTable* table = hash_table_create(string_compare, string_hash);
    insert_word(table, "example");
    insert_word(table, "example");

    const int* freq = (int*) hash_table_get(table, "example");
    TEST_ASSERT_NOT_NULL(freq);
    TEST_ASSERT_EQUAL_INT(2, *freq);

    void** keys = hash_table_keyset(table);
    free(keys[0]);
    free(keys);

    void** values = hash_table_values(table);
    free(values[0]);
    free(values);

    hash_table_free(table);
}

/**
 * @brief Test case for inserting a new word into the hash table.
 *
 * This test case checks the behavior of the `insert_word` function when
 * inserting a new word into the hash table. It ensures that the function
 * correctly adds the new word with a frequency of 1.
 */
void test_insert_word_new_word(void) {
    HashTable* table = hash_table_create(string_compare, string_hash);
    int result = insert_word(table, "newword");
    TEST_ASSERT_EQUAL_INT(0, result);

    const int* freq = (int*) hash_table_get(table, "newword");
    TEST_ASSERT_NOT_NULL(freq);
    TEST_ASSERT_EQUAL_INT(1, *freq);

    void** keys = hash_table_keyset(table);
    free(keys[0]);
    free(keys);

    free((void*) freq);

    hash_table_free(table);
}
