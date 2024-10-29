#include "unity.h"
#include "test_edit_distance.h"


void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

int main(void) {
    UNITY_BEGIN();

    // Run tests for recursive edit_distance
    RUN_TEST(test_edit_distance_identical_strings_recursive);
    RUN_TEST(test_edit_distance_empty_string_recursive);
    RUN_TEST(test_edit_distance_insertion_recursive);
    RUN_TEST(test_edit_distance_deletion_recursive);
    RUN_TEST(test_edit_distance_substitution_recursive);
    RUN_TEST(test_edit_distance_mixed_operations_recursive);
    RUN_TEST(test_edit_distance_null_string_recursive);

    // Run tests for dynamic programming edit_distance_dyn
    RUN_TEST(test_edit_distance_identical_strings_dynamic);
    RUN_TEST(test_edit_distance_empty_string_dynamic);
    RUN_TEST(test_edit_distance_insertion_dynamic);
    RUN_TEST(test_edit_distance_deletion_dynamic);
    RUN_TEST(test_edit_distance_substitution_dynamic);
    RUN_TEST(test_edit_distance_mixed_operations_dynamic);
    RUN_TEST(test_edit_distance_null_string_dynamic);

    return UNITY_END();
}