#include "unity.h"
#include "test_hashtable.h"


void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

int main() {
    UNITY_BEGIN();

    // hash table tests: basic operations
    RUN_TEST(test_hash_table_create);
    RUN_TEST(test_hash_table_put);
    RUN_TEST(test_hash_table_get);
    RUN_TEST(test_hash_table_contains_key);
    RUN_TEST(test_hash_table_remove);
    RUN_TEST(test_hash_table_size);
    RUN_TEST(test_hash_table_keyset);
    RUN_TEST(test_hash_table_free);
    RUN_TEST(test_hash_table_resize);
    RUN_TEST(test_hash_table_load_factor);
    RUN_TEST(test_hash_table_replace);
    RUN_TEST(test_hash_table_clear);
    RUN_TEST(test_hash_table_map);
    RUN_TEST(test_hash_table_values);
    RUN_TEST(test_hash_table_equals);
    RUN_TEST(test_hash_table_copy);
    RUN_TEST(test_hash_table_merge);

    return UNITY_END();
}