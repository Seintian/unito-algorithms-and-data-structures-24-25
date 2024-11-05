#include "unity.h"
#include "../src/hashtable.h"
#include <string.h>
#include <stdlib.h>


// Hash function for testing
unsigned long simple_hash(const void* key) {
    return (unsigned long)key % 100;
}

// Compare function for testing
int int_compare(const void* a, const void* b) {
    return (int)(long)a - (int)(long)b;
}

// Variables for use in tests
HashTable* table;

void setUp(void) {
    table = hash_table_create(int_compare, simple_hash);
}

void tearDown(void) {
    hash_table_free(table);
}

// Test creation of hash table
void test_hash_table_create(void) {
    TEST_ASSERT_NOT_NULL(table);
    TEST_ASSERT_EQUAL(0, hash_table_size(table));
    TEST_ASSERT_EQUAL(16, hash_table_capacity(table));
}

// Test insertion and retrieval
void test_hash_table_put_and_get(void) {
    hash_table_put(table, (void*)1, (void*)100);
    hash_table_put(table, (void*)2, (void*)200);

    TEST_ASSERT_EQUAL((void*)100, hash_table_get(table, (void*)1));
    TEST_ASSERT_EQUAL((void*)200, hash_table_get(table, (void*)2));
}

// Test update of an existing key
void test_hash_table_update_existing_key(void) {
    hash_table_put(table, (void*)1, (void*)100);
    hash_table_put(table, (void*)1, (void*)150);

    TEST_ASSERT_EQUAL((void*)150, hash_table_get(table, (void*)1));
}

// Test check for key existence
void test_hash_table_contains_key(void) {
    hash_table_put(table, (void*)1, (void*)100);

    TEST_ASSERT_TRUE(hash_table_contains_key(table, (void*)1));
    TEST_ASSERT_FALSE(hash_table_contains_key(table, (void*)99));
}

// Test removing a key-value pair
void test_hash_table_remove(void) {
    hash_table_put(table, (void*)1, (void*)100);
    hash_table_remove(table, (void*)1);

    TEST_ASSERT_FALSE(hash_table_contains_key(table, (void*)1));
    TEST_ASSERT_NULL(hash_table_get(table, (void*)1));
}

// Test retrieval of all keys
void test_hash_table_keyset(void) {
    hash_table_put(table, (void*)1, (void*)100);
    hash_table_put(table, (void*)2, (void*)200);

    void** keys = hash_table_keyset(table);
    TEST_ASSERT_NOT_NULL(keys);
    TEST_ASSERT_EQUAL_PTR((void*)1, keys[0]);
    TEST_ASSERT_EQUAL_PTR((void*)2, keys[1]);
    free(keys);
}

// Test retrieval of all values
void test_hash_table_values(void) {
    hash_table_put(table, (void*)1, (void*)100);
    hash_table_put(table, (void*)2, (void*)200);

    void** values = hash_table_values(table);
    TEST_ASSERT_NOT_NULL(values);
    TEST_ASSERT_EQUAL_PTR((void*)100, values[0]);
    TEST_ASSERT_EQUAL_PTR((void*)200, values[1]);
    free(values);
}

// Test clear all elements from the hash table
void test_hash_table_clear(void) {
    hash_table_put(table, (void*)1, (void*)100);
    hash_table_clear(table);

    TEST_ASSERT_EQUAL(0, hash_table_size(table));
    TEST_ASSERT_FALSE(hash_table_contains_key(table, (void*)1));
}

// Test hash table load factor
void test_hash_table_load_factor(void) {
    hash_table_put(table, (void*)1, (void*)100);
    float load_factor = hash_table_load_factor(table);
    TEST_ASSERT_FLOAT_WITHIN(0.1, 0.0625, load_factor);
}

// Test replacing a value for an existing key
void test_hash_table_replace(void) {
    hash_table_put(table, (void*)1, (void*)100);
    hash_table_replace(table, (void*)1, (void*)300);

    TEST_ASSERT_EQUAL((void*)300, hash_table_get(table, (void*)1));
}

void map_function(const void* key, const void* value) {
    int new_value = (int)(long)value * 2;
    hash_table_replace(table, key, (void*)(long)new_value);
}

void test_hash_table_map(void) {
    hash_table_put(table, (void*)1, (void*)100);
    hash_table_put(table, (void*)2, (void*)200);

    hash_table_map(table, map_function);

    TEST_ASSERT_EQUAL((void*)200, hash_table_get(table, (void*)1));
    TEST_ASSERT_EQUAL((void*)400, hash_table_get(table, (void*)2));
}

// Test hash table equality check
void test_hash_table_equals(void) {
    HashTable* table2 = hash_table_create(int_compare, simple_hash);

    hash_table_put(table, (void*)1, (void*)100);
    hash_table_put(table2, (void*)1, (void*)100);

    TEST_ASSERT_TRUE(hash_table_equals(table, table2));

    hash_table_put(table2, (void*)2, (void*)200);
    TEST_ASSERT_FALSE(hash_table_equals(table, table2));

    hash_table_free(table2);
}

// Test deep copy of hash table
void test_hash_table_copy(void) {
    hash_table_put(table, (void*)1, (void*)100);
    hash_table_put(table, (void*)2, (void*)200);

    HashTable* copy = hash_table_copy(table);
    TEST_ASSERT_TRUE(hash_table_equals(table, copy));

    hash_table_free(copy);
}

// Test merging two hash tables
void test_hash_table_merge(void) {
    HashTable* source = hash_table_create(int_compare, simple_hash);

    hash_table_put(table, (void*)1, (void*)100);
    hash_table_put(source, (void*)2, (void*)200);

    hash_table_merge(table, source);

    TEST_ASSERT_EQUAL((void*)100, hash_table_get(table, (void*)1));
    TEST_ASSERT_EQUAL((void*)200, hash_table_get(table, (void*)2));

    hash_table_free(source);
}

// Test resizing and rehashing
void test_hash_table_resized(void) {
    // Insert enough elements to exceed the load factor threshold
    for (int i = 0; i < 20; i++) {
        hash_table_put(table, (void*)(long)i, (void*)(long)(i * 10));
    }

    // Verify that all keys are accessible after resizing
    for (int i = 0; i < 20; i++) {
        TEST_ASSERT_EQUAL((void*)(long)(i * 10), hash_table_get(table, (void*)(long)i));
    }
}
