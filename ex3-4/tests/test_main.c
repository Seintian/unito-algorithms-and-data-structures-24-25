#include "unity.h"
#include "test_hashtable.h"


int main() {
    UNITY_BEGIN();

    // hash table tests: basic operations
    RUN_TEST(test_hash_table_create);
    RUN_TEST(test_hash_table_put_and_get);
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
    RUN_TEST(test_hash_table_resized);

    return UNITY_END();
}