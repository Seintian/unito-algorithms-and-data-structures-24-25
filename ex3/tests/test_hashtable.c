/**
 * @file test_hashtable.c
 * @brief Unit tests for the hash table implementation.
 *
 * This file contains the implementation of unit tests for the hash table data structure.
 */

#include "unity.h"
#include "hashtable.h"
#include "prime.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


/**
 * @brief Hash function for testing with strings.
 * 
 * This function implements the DJB2 hash algorithm for string keys.
 * 
 * @param key The key to hash.
 * @return The computed hash value.
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
 * This function compares two strings using the standard `strcmp` function.
 * 
 * @param a The first string to compare.
 * @param b The second string to compare.
 * @return An integer less than, equal to, or greater than zero if a is found to be less than, equal to, or greater than b.
 */
static int string_compare(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

// Global variable for the hash table used in tests
HashTable* table;

/**
 * @brief Set up the test environment.
 * 
 * Initializes a new hash table before each test.
 */
void setUp(void) {
    table = hash_table_create(string_compare, string_hash);
}

/**
 * @brief Clean up the test environment.
 * 
 * Frees the allocated memory for the hash table after each test.
 */
void tearDown(void) {
    hash_table_free(table);
    table = NULL;
}

/**
 * @brief Test the creation of a hash table.
 * 
 * Verifies that a new hash table is created and is empty, with the correct initial capacity.
 */
void test_hash_table_create(void) {
    TEST_ASSERT_NOT_NULL(table);
    TEST_ASSERT_EQUAL(0, hash_table_size(table));
    TEST_ASSERT_EQUAL(next_prime(16), hash_table_capacity(table));
}

/**
 * @brief Test insertion and retrieval of key-value pairs.
 * 
 * Verifies that keys can be inserted and values can be retrieved correctly.
 */
void test_hash_table_put_and_get(void) {
    hash_table_put(table, "key1", "value1");
    hash_table_put(table, "key2", "value2");

    TEST_ASSERT_EQUAL_STRING("value1", (char*)hash_table_get(table, "key1"));
    TEST_ASSERT_EQUAL_STRING("value2", (char*)hash_table_get(table, "key2"));
}

/**
 * @brief Test updating an existing key.
 * 
 * Verifies that inserting a value with an existing key updates the value correctly.
 */
void test_hash_table_update_existing_key(void) {
    hash_table_put(table, "key1", "value1");
    hash_table_put(table, "key1", "newValue");

    TEST_ASSERT_EQUAL_STRING("newValue", (char*)hash_table_get(table, "key1"));
}

/**
 * @brief Test checking for key existence.
 * 
 * Verifies that the `hash_table_contains_key` function correctly identifies whether a key exists in the table.
 */
void test_hash_table_contains_key(void) {
    hash_table_put(table, "key1", "value1");

    TEST_ASSERT_TRUE(hash_table_contains_key(table, "key1"));
    TEST_ASSERT_FALSE(hash_table_contains_key(table, "key99"));
}

/**
 * @brief Test removing a key-value pair.
 * 
 * Verifies that a key-value pair can be removed from the hash table.
 */
void test_hash_table_remove(void) {
    hash_table_put(table, "key1", "value1");
    hash_table_remove(table, "key1");

    TEST_ASSERT_FALSE(hash_table_contains_key(table, "key1"));
    TEST_ASSERT_NULL(hash_table_get(table, "key1"));
}

/**
 * @brief Test retrieval of all keys in the hash table.
 * 
 * Verifies that all keys in the hash table can be retrieved correctly.
 */
void test_hash_table_keyset(void) {
    hash_table_put(table, "key1", "value1");
    hash_table_put(table, "key2", "value2");

    void** keys = hash_table_keyset(table);
    TEST_ASSERT_NOT_NULL(keys);

    int foundKey1 = 0;
    int foundKey2 = 0;
    for (int i = 0; i < hash_table_size(table); i++) {
        if (strcmp((char*)keys[i], "key1") == 0) {
            foundKey1 = 1;
        }
        if (strcmp((char*)keys[i], "key2") == 0) {
            foundKey2 = 1;
        }
    }
    TEST_ASSERT_TRUE(foundKey1);
    TEST_ASSERT_TRUE(foundKey2);

    free(keys);
}

/**
 * @brief Test retrieval of all values in the hash table.
 * 
 * Verifies that all values in the hash table can be retrieved correctly.
 */
void test_hash_table_values(void) {
    hash_table_put(table, "key1", "value1");
    hash_table_put(table, "key2", "value2");

    void** values = hash_table_values(table);
    TEST_ASSERT_NOT_NULL(values);

    int foundValue1 = 0;
    int foundValue2 = 0;
    for (int i = 0; i < hash_table_size(table); i++) {
        if (strcmp((char*)values[i], "value1") == 0) {
            foundValue1 = 1;
        }
        if (strcmp((char*)values[i], "value2") == 0) {
            foundValue2 = 1;
        }
    }
    TEST_ASSERT_TRUE(foundValue1);
    TEST_ASSERT_TRUE(foundValue2);

    free(values);
}

/**
 * @brief Test resizing of the hash table.
 * 
 * Verifies that the hash table resizes when the number of elements exceeds the threshold.
 */
void test_hash_table_resize_up(void) {
    for (int i = 0; i < 20; i++) {
        char key[10];
        snprintf(key, sizeof(key), "key%d", i);
        hash_table_put(table, key, "value");
    }

    TEST_ASSERT_GREATER_THAN(16, hash_table_capacity(table));
}

/**
 * @brief Test copying of a hash table.
 * 
 * Verifies that a hash table can be copied correctly, preserving the keys and values.
 */
void test_hash_table_copy(void) {
    hash_table_put(table, "key1", "value1");
    hash_table_put(table, "key2", "value2");

    HashTable* copiedTable = hash_table_copy(table);
    TEST_ASSERT_NOT_NULL(copiedTable);
    TEST_ASSERT_EQUAL(hash_table_size(table), hash_table_size(copiedTable));
    TEST_ASSERT_EQUAL_STRING("value1", (char*)hash_table_get(copiedTable, "key1"));
    TEST_ASSERT_EQUAL_STRING("value2", (char*)hash_table_get(copiedTable, "key2"));

    hash_table_free(copiedTable);
}

/**
 * @brief Test clearing the hash table.
 * 
 * Verifies that the hash table can be cleared, removing all key-value pairs.
 */
void test_hash_table_clear(void) {
    hash_table_put(table, "key1", "value1");
    hash_table_put(table, "key2", "value2");
    hash_table_clear(table);

    TEST_ASSERT_EQUAL(0, hash_table_size(table));
    TEST_ASSERT_NULL(hash_table_get(table, "key1"));
    TEST_ASSERT_NULL(hash_table_get(table, "key2"));
}

/**
 * @brief Test load factor of the hash table.
 * 
 * Verifies that the load factor of the hash table is within expected limits.
 */
void test_hash_table_load_factor(void) {
    hash_table_put(table, "key1", "value1");
    hash_table_put(table, "key2", "value2");

    float load_factor = hash_table_load_factor(table);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 2.0 / hash_table_capacity(table), load_factor);
}

/**
 * @brief Test replacing an existing key's value.
 * 
 * Verifies that the `hash_table_replace` function correctly replaces the value of an existing key.
 */
void test_hash_table_replace(void) {
    hash_table_put(table, "key1", "value1");
    hash_table_replace(table, "key1", "new_value1");

    void* value = hash_table_get(table, "key1");
    TEST_ASSERT_EQUAL_STRING("new_value1", (char*)value);
}

/**
 * @brief Helper function to convert values to uppercase.
 * 
 * This function is used in the `test_hash_table_map` test to convert all values to uppercase.
 * 
 * @param key The key associated with the value.
 * @param value The value to modify.
 */
static void set_values_to_uppercase(const void* key, const void* value) {
    char* new_value = strdup((char*)value);
    for (size_t i = 0; i < strlen(new_value); i++) {
        new_value[i] = toupper(new_value[i]);
    }

    hash_table_put(table, key, new_value);
}

/**
 * @brief Free allocated memory for key-value pairs.
 * 
 * This function is used to free memory for keys and values in the `test_hash_table_map` test.
 * 
 * @param key The key to free.
 * @param value The value to free.
 */
void free_key_value(const void* key, const void* value) {
    free((void*) key);
    free((void*) value);
}

/**
 * @brief Test applying a function to all elements in the hash table.
 * 
 * Verifies that the `hash_table_map` function correctly applies a function to all key-value pairs.
 */
void test_hash_table_map(void) {
    char* value1 = strdup("value1");
    char* value2 = strdup("value2");

    hash_table_put(table, strdup("key1"), value1);
    hash_table_put(table, strdup("key2"), value2);

    hash_table_map(table, set_values_to_uppercase);

    TEST_ASSERT_EQUAL_STRING("VALUE1", hash_table_get(table, "key1"));
    TEST_ASSERT_EQUAL_STRING("VALUE2", hash_table_get(table, "key2"));

    free(value1);
    free(value2);

    hash_table_map(table, free_key_value);
}

/**
 * @brief Test equality of two hash tables.
 * 
 * Verifies that two hash tables with the same content are considered equal.
 */
void test_hash_table_equals(void) {
    HashTable* table1 = hash_table_create(string_compare, string_hash);
    HashTable* table2 = hash_table_create(string_compare, string_hash);
    TEST_ASSERT_NOT_NULL(table1);
    TEST_ASSERT_NOT_NULL(table2);

    hash_table_put(table1, "key1", "value1");
    hash_table_put(table2, "key1", "value1");

    int result = hash_table_equals(table1, table2, string_compare);
    TEST_ASSERT_EQUAL_INT(1, result);

    hash_table_put(table2, "key2", "value2");
    result = hash_table_equals(table1, table2, string_compare);
    TEST_ASSERT_EQUAL_INT(0, result);

    hash_table_free(table1);
    hash_table_free(table2);
}

/**
 * @brief Test merging two hash tables.
 * 
 * Verifies that the `hash_table_merge` function correctly merges two hash tables.
 */
void test_hash_table_merge(void) {
    HashTable* table1 = hash_table_create(string_compare, string_hash);
    HashTable* table2 = hash_table_create(string_compare, string_hash);
    TEST_ASSERT_NOT_NULL(table1);
    TEST_ASSERT_NOT_NULL(table2);

    hash_table_put(table1, "key1", "value1");
    hash_table_put(table2, "key2", "value2");

    hash_table_merge(table1, table2);

    void* value1 = hash_table_get(table1, "key1");
    void* value2 = hash_table_get(table1, "key2");

    TEST_ASSERT_EQUAL_STRING("value1", (char*)value1);
    TEST_ASSERT_EQUAL_STRING("value2", (char*)value2);

    hash_table_free(table1);
    hash_table_free(table2);
}

/**
 * @brief Test resizing of the hash table.
 * 
 * Verifies that the hash table resizes when the number of elements exceeds the threshold.
 */
void test_hash_table_resized(void) {
    for (int i = 0; i < 20; i++) {
        char key[10];
        snprintf(key, sizeof(key), "key%d", i);
        hash_table_put(table, key, "value");
    }

    TEST_ASSERT_GREATER_THAN(16, hash_table_capacity(table));
}
