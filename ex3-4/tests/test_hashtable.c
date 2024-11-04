#include "test_hashtable.h"
#include "../src/hashtable.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// Comparison function
int compare(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

// Hash function
unsigned long hash_func(const void* key) {
    const char* str = (const char*)key;
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) hash = ((hash << 5) + hash) + c;
    return hash;
}

// Function to apply to each key-value pair
void my_function(void* key, void* value) {
    printf("Key: %s, Value: %s\n", (char*)key, (char*)value);
}


void test_hash_table_create() {
    HashTable* table = hash_table_create(compare, hash_func);
    TEST_ASSERT_NOT_NULL(table);
    TEST_ASSERT_EQUAL(0, hash_table_size(table));
    hash_table_free(table);
}

void test_hash_table_put() {
    HashTable* table = hash_table_create(compare, hash_func);
    hash_table_put(table, "key1", "value1");
    TEST_ASSERT_EQUAL_STRING("value1", hash_table_get(table, "key1"));
    TEST_ASSERT_EQUAL(1, hash_table_size(table));
    hash_table_free(table);
}

void test_hash_table_get() {
    HashTable* table = hash_table_create(compare, hash_func);
    hash_table_put(table, "key1", "value1");
    TEST_ASSERT_EQUAL_STRING("value1", hash_table_get(table, "key1"));
    TEST_ASSERT_NULL(hash_table_get(table, "key2")); // Non-existent key
    hash_table_free(table);
}

void test_hash_table_contains_key() {
    HashTable* table = hash_table_create(compare, hash_func);
    hash_table_put(table, "key1", "value1");
    TEST_ASSERT_TRUE(hash_table_contains_key(table, "key1"));
    TEST_ASSERT_FALSE(hash_table_contains_key(table, "key2"));
    hash_table_free(table);
}

void test_hash_table_remove() {
    HashTable* table = hash_table_create(compare, hash_func);
    hash_table_put(table, "key1", "value1");
    hash_table_remove(table, "key1");
    TEST_ASSERT_NULL(hash_table_get(table, "key1"));
    TEST_ASSERT_EQUAL(0, hash_table_size(table));
    hash_table_free(table);
}

void test_hash_table_size() {
    HashTable* table = hash_table_create(compare, hash_func);
    hash_table_put(table, "key1", "value1");
    TEST_ASSERT_EQUAL(1, hash_table_size(table));
    hash_table_free(table);
}

void test_hash_table_keyset() {
    HashTable* table = hash_table_create(compare, hash_func);
    hash_table_put(table, "key1", "value1");
    hash_table_put(table, "key2", "value2");
    void** keys = hash_table_keyset(table);
    TEST_ASSERT_EQUAL_STRING("key1", (char*)keys[0]);
    TEST_ASSERT_EQUAL_STRING("key2", (char*)keys[1]);
    free(keys);
    hash_table_free(table);
}

void test_hash_table_free() {
    HashTable* table = hash_table_create(compare, hash_func);
    hash_table_put(table, "key1", "value1");
    hash_table_free(table);
}

void test_hash_table_resize() {
    HashTable* table = hash_table_create(compare, hash_func);
    for (int i = 0; i < 100; i++) {
        char key[10];
        sprintf(key, "key%d", i);
        hash_table_put(table, key, "value");
    }
    TEST_ASSERT_EQUAL(100, hash_table_size(table));
    hash_table_free(table);
}

void test_hash_table_load_factor() {
    HashTable* table = hash_table_create(compare, hash_func);
    hash_table_put(table, "key1", "value1");
    float load_factor = hash_table_load_factor(table);
    TEST_ASSERT(load_factor > 0.0);
    hash_table_free(table);
}

void test_hash_table_replace() {
    HashTable* table = hash_table_create(compare, hash_func);
    hash_table_put(table, "key1", "value1");
    hash_table_replace(table, "key1", "new_value");
    TEST_ASSERT_EQUAL_STRING("new_value", hash_table_get(table, "key1"));
    hash_table_free(table);
}

void test_hash_table_clear() {
    HashTable* table = hash_table_create(compare, hash_func);
    hash_table_put(table, "key1", "value1");
    hash_table_clear(table);
    TEST_ASSERT_EQUAL(0, hash_table_size(table));
    hash_table_free(table);
}

void test_hash_table_map() {
    HashTable* table = hash_table_create(compare, hash_func);
    hash_table_put(table, "key1", "value1");
    // Assuming a function applies and updates elements
    hash_table_map(table, my_function);
    hash_table_free(table);
}

void test_hash_table_values() {
    HashTable* table = hash_table_create(compare, hash_func);
    hash_table_put(table, "key1", "value1");
    hash_table_put(table, "key2", "value2");
    void** values = hash_table_values(table);
    TEST_ASSERT_EQUAL_STRING("value1", (char*)values[0]);
    TEST_ASSERT_EQUAL_STRING("value2", (char*)values[1]);
    free(values);
    hash_table_free(table);
}

void test_hash_table_equals() {
    HashTable* table1 = hash_table_create(compare, hash_func);
    HashTable* table2 = hash_table_create(compare, hash_func);
    hash_table_put(table1, "key1", "value1");
    hash_table_put(table2, "key1", "value1");
    TEST_ASSERT_TRUE(hash_table_equals(table1, table2));
    hash_table_free(table1);
    hash_table_free(table2);
}

void test_hash_table_copy() {
    HashTable* table = hash_table_create(compare, hash_func);
    hash_table_put(table, "key1", "value1");
    HashTable* copy = hash_table_copy(table);
    TEST_ASSERT_EQUAL_STRING("value1", hash_table_get(copy, "key1"));
    hash_table_free(table);
    hash_table_free(copy);
}

void test_hash_table_merge() {
    HashTable* dest = hash_table_create(compare, hash_func);
    HashTable* source = hash_table_create(compare, hash_func);
    hash_table_put(source, "key1", "value1");
    hash_table_merge(dest, source);
    TEST_ASSERT_EQUAL_STRING("value1", hash_table_get(dest, "key1"));
    hash_table_free(dest);
    hash_table_free(source);
}
