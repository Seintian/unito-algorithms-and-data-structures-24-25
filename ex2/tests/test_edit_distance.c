#include "test_edit_distance.h"


/* Tests for edit_distance (recursive approach) */
void test_edit_distance_identical_strings_recursive(void) {
    TEST_ASSERT_EQUAL_INT(0, edit_distance("hello", "hello"));
}

void test_edit_distance_empty_string_recursive(void) {
    TEST_ASSERT_EQUAL_INT(5, edit_distance("hello", ""));
    TEST_ASSERT_EQUAL_INT(5, edit_distance("", "hello"));
}

void test_edit_distance_insertion_recursive(void) {
    TEST_ASSERT_EQUAL_INT(1, edit_distance("hello", "helloo"));
}

void test_edit_distance_deletion_recursive(void) {
    TEST_ASSERT_EQUAL_INT(1, edit_distance("helloo", "hello"));
}

void test_edit_distance_substitution_recursive(void) {
    TEST_ASSERT_EQUAL_INT(2, edit_distance("hello", "jello"));
}

void test_edit_distance_mixed_operations_recursive(void) {
    TEST_ASSERT_EQUAL_INT(4, edit_distance("sunday", "saturday"));
}

void test_edit_distance_null_string_recursive(void) {
    TEST_ASSERT_EQUAL_INT(-1, edit_distance(NULL, "test"));
    TEST_ASSERT_EQUAL_INT(-1, edit_distance("test", NULL));
}

/* Tests for edit_distance_dyn (dynamic programming approach) */
void test_edit_distance_identical_strings_dynamic(void) {
    TEST_ASSERT_EQUAL_INT(0, edit_distance_dyn("hello", "hello"));
}

void test_edit_distance_empty_string_dynamic(void) {
    TEST_ASSERT_EQUAL_INT(5, edit_distance_dyn("hello", ""));
    TEST_ASSERT_EQUAL_INT(5, edit_distance_dyn("", "hello"));
}

void test_edit_distance_insertion_dynamic(void) {
    TEST_ASSERT_EQUAL_INT(1, edit_distance_dyn("hello", "helloo"));
}

void test_edit_distance_deletion_dynamic(void) {
    TEST_ASSERT_EQUAL_INT(1, edit_distance_dyn("helloo", "hello"));
}

void test_edit_distance_substitution_dynamic(void) {
    TEST_ASSERT_EQUAL_INT(2, edit_distance_dyn("hello", "jello"));
}

void test_edit_distance_mixed_operations_dynamic(void) {
    TEST_ASSERT_EQUAL_INT(4, edit_distance_dyn("sunday", "saturday"));
}

void test_edit_distance_null_string_dynamic(void) {
    TEST_ASSERT_EQUAL_INT(-1, edit_distance_dyn(NULL, "test"));
    TEST_ASSERT_EQUAL_INT(-1, edit_distance_dyn("test", NULL));
}