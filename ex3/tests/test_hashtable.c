/**
 * @file test_hashtable.c
 * @brief Unit tests for the hash table implementation.
 */

#include "unity.h"
#include "hashtable.h"
#include "prime.h"
#include <string.h>
#include <stdlib.h>


// Hash function for testing with strings
unsigned long string_hash(const void* key) {
    const char* str = (const char*)key;
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % 100;
}

// Compare function for strings
int string_compare(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

// Variables for use in tests
HashTable* table;

void setUp(void) {
    table = hash_table_create(string_compare, string_hash);
}

void tearDown(void) {
    hash_table_free(table);
    table = NULL;
}

// Test creation of hash table
void test_hash_table_create(void) {
    TEST_ASSERT_NOT_NULL(table);
    TEST_ASSERT_EQUAL(0, hash_table_size(table));
    TEST_ASSERT_EQUAL(next_prime(16), hash_table_capacity(table));
}

// Test insertion and retrieval
void test_hash_table_put_and_get(void) {
    hash_table_put(table, "key1", "value1");
    hash_table_put(table, "key2", "value2");

    TEST_ASSERT_EQUAL_STRING("value1", (char*)hash_table_get(table, "key1"));
    TEST_ASSERT_EQUAL_STRING("value2", (char*)hash_table_get(table, "key2"));
}

// Test update of an existing key
void test_hash_table_update_existing_key(void) {
    hash_table_put(table, "key1", "value1");
    hash_table_put(table, "key1", "newValue");

    TEST_ASSERT_EQUAL_STRING("newValue", (char*)hash_table_get(table, "key1"));
}

// Test check for key existence
void test_hash_table_contains_key(void) {
    hash_table_put(table, "key1", "value1");

    TEST_ASSERT_TRUE(hash_table_contains_key(table, "key1"));
    TEST_ASSERT_FALSE(hash_table_contains_key(table, "key99"));
}

// Test removing a key-value pair
void test_hash_table_remove(void) {
    hash_table_put(table, "key1", "value1");
    hash_table_remove(table, "key1");

    TEST_ASSERT_FALSE(hash_table_contains_key(table, "key1"));
    TEST_ASSERT_NULL(hash_table_get(table, "key1"));
}

// Test retrieval of all keys
void test_hash_table_keyset(void) {
    hash_table_put(table, "key1", "value1");
    hash_table_put(table, "key2", "value2");

    char** keys = (char**)hash_table_keyset(table);
    TEST_ASSERT_NOT_NULL(keys);
    TEST_ASSERT_EQUAL_STRING("key1", keys[0]);
    TEST_ASSERT_EQUAL_STRING("key2", keys[1]);
    free(keys);
}

// Test retrieval of all values
void test_hash_table_values(void) {
    hash_table_put(table, "key1", "value1");
    hash_table_put(table, "key2", "value2");

    char** values = (char**)hash_table_values(table);
    TEST_ASSERT_NOT_NULL(values);
    TEST_ASSERT_EQUAL_STRING("value1", values[0]);
    TEST_ASSERT_EQUAL_STRING("value2", values[1]);
    free(values);
}

// Test clear all elements from the hash table
void test_hash_table_clear(void) {
    hash_table_put(table, "key1", "value1");
    hash_table_clear(table);

    TEST_ASSERT_EQUAL(0, hash_table_size(table));
    TEST_ASSERT_FALSE(hash_table_contains_key(table, "key1"));
}

// Test hash table load factor
void test_hash_table_load_factor(void) {
    hash_table_put(table, "key1", "value1");
    float load_factor = hash_table_load_factor(table);
    TEST_ASSERT_FLOAT_WITHIN(0.1, 0.0625, load_factor);
}

// Test replacing a value for an existing key
void test_hash_table_replace(void) {
    hash_table_put(table, "key1", "value1");
    hash_table_replace(table, "key1", "replacedValue");

    TEST_ASSERT_EQUAL_STRING("replacedValue", (char*)hash_table_get(table, "key1"));
}

void map_function(const void* key, const void* value) {
    char* new_value = strdup((const char*)value);
    strcat(new_value, "_mapped");
    hash_table_replace(table, key, new_value);
    free(new_value); // Assumes hash_table_replace copies the string, adjust if needed
}

void test_hash_table_map(void) {
    hash_table_put(table, "key1", "value1");
    hash_table_put(table, "key2", "value2");

    hash_table_map(table, map_function);

    TEST_ASSERT_EQUAL_STRING("value1_mapped", (char*)hash_table_get(table, "key1"));
    TEST_ASSERT_EQUAL_STRING("value2_mapped", (char*)hash_table_get(table, "key2"));
}

// Test hash table equality check
void test_hash_table_equals(void) {
    HashTable* table2 = hash_table_create(string_compare, string_hash);

    hash_table_put(table, "key1", "value1");
    hash_table_put(table2, "key1", "value1");

    TEST_ASSERT_TRUE(hash_table_equals(table, table2, string_compare));

    hash_table_put(table2, "key2", "value2");
    TEST_ASSERT_FALSE(hash_table_equals(table, table2, string_compare));

    hash_table_free(table2);
}

// Test deep copy of hash table
void test_hash_table_copy(void) {
    hash_table_put(table, "key1", "value1");
    hash_table_put(table, "key2", "value2");

    HashTable* copy = hash_table_copy(table);
    TEST_ASSERT_TRUE(hash_table_equals(table, copy, string_compare));

    hash_table_free(copy);
}

// Test merging two hash tables
void test_hash_table_merge(void) {
    HashTable* source = hash_table_create(string_compare, string_hash);

    hash_table_put(table, "key1", "value1");
    hash_table_put(source, "key2", "value2");

    hash_table_merge(table, source);

    TEST_ASSERT_EQUAL_STRING("value1", (char*)hash_table_get(table, "key1"));
    TEST_ASSERT_EQUAL_STRING("value2", (char*)hash_table_get(table, "key2"));

    hash_table_free(source);
}

// Test resizing and rehashing
void test_hash_table_resized(void) {
    // Insert enough elements to exceed the load factor threshold
    for (int i = 0; i < 20; i++) {
        char key[10];
        char value[10];
        sprintf(key, "key%d", i);
        sprintf(value, "value%d", i);
        hash_table_put(table, strdup(key), strdup(value));
    }

    // Verify that all keys are accessible after resizing
    for (int i = 0; i < 20; i++) {
        char key[10];
        char value[10];
        sprintf(key, "key%d", i);
        sprintf(value, "value%d", i);
        TEST_ASSERT_EQUAL_STRING(value, (char*)hash_table_get(table, key));
    }

    TEST_ASSERT_EQUAL_INT(next_prime(32), hash_table_capacity(table));

    // Cleanup
    for (int i = 0; i < 20; i++) {
        char key[10];
        sprintf(key, "key%d", i);
        free((char*)hash_table_get(table, key));
    }
}
