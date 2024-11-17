/**
 * @file test_hashtable.c
 * @brief Unit tests for the hash table implementation.
 */

#include "unity.h"
#include "hashtable.h"
#include "prime.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


// Hash function for testing with strings
static unsigned long string_hash(const void* key) {
    const char* str = (const char*)key;
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash;
}

// Compare function for strings
static int string_compare(const void* a, const void* b) {
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

// Test retrieval of all values
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

// Test resizing behavior
void test_hash_table_resize_up(void) {
    for (int i = 0; i < 20; i++) {
        char key[10];
        snprintf(key, sizeof(key), "key%d", i);
        hash_table_put(table, key, "value");
    }

    TEST_ASSERT_GREATER_THAN(16, hash_table_capacity(table));
}

// Test copying of a hash table
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

// Test hash table clear function
void test_hash_table_clear(void) {
    hash_table_put(table, "key1", "value1");
    hash_table_put(table, "key2", "value2");
    hash_table_clear(table);

    TEST_ASSERT_EQUAL(0, hash_table_size(table));
    TEST_ASSERT_NULL(hash_table_get(table, "key1"));
    TEST_ASSERT_NULL(hash_table_get(table, "key2"));
}

void test_hash_table_load_factor(void) {
    hash_table_put(table, "key1", "value1");
    hash_table_put(table, "key2", "value2");

    float load_factor = hash_table_load_factor(table);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 2.0 / hash_table_capacity(table), load_factor);
}

void test_hash_table_replace(void) {
    hash_table_put(table, "key1", "value1");
    hash_table_replace(table, "key1", "new_value1");

    void* value = hash_table_get(table, "key1");
    TEST_ASSERT_EQUAL_STRING("new_value1", (char*)value);
}

void set_values_to_uppercase(const void* key, const void* value) {
    char* new_value = strdup((char*)value);
    for (int i = 0; i < strlen(new_value); i++) {
        new_value[i] = toupper(new_value[i]);
    }

    hash_table_put(table, key, new_value);
}

void free_key_value(const void* key, const void* value) {
    free((void*)key);
    free((void*)value);
}

void test_hash_table_map(void) {
    hash_table_put(table, strdup("key1"), strdup("value1"));
    hash_table_put(table, strdup("key2"), strdup("value2"));

    hash_table_map(table, set_values_to_uppercase);

    void* value1 = hash_table_get(table, "key1");
    void* value2 = hash_table_get(table, "key2");

    TEST_ASSERT_EQUAL_STRING("VALUE1", (char*)value1);
    TEST_ASSERT_EQUAL_STRING("VALUE2", (char*)value2);

    hash_table_map(table, free_key_value);
}

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

void test_hash_table_resized(void) {
    for (int i = 0; i < 20; i++) {
        char key[10];
        snprintf(key, sizeof(key), "key%d", i);
        hash_table_put(table, key, "value");
    }

    TEST_ASSERT_GREATER_THAN(16, hash_table_capacity(table));
}
