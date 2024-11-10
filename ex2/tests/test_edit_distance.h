/**
 * @file test_edit_distance.h
 * @brief Unit tests for the edit_distance algorithm.
 */

#include "unity.h"
#include "edit_distance.h"

#ifndef _TEST_EDIT_DISTANCE_H_
#define _TEST_EDIT_DISTANCE_H_


void test_edit_distance_identical_strings_recursive(void);
void test_edit_distance_empty_string_recursive(void);
void test_edit_distance_insertion_recursive(void);
void test_edit_distance_deletion_recursive(void);
void test_edit_distance_substitution_recursive(void);
void test_edit_distance_mixed_operations_recursive(void);
void test_edit_distance_null_string_recursive(void);
void test_edit_distance_identical_strings_dynamic(void);
void test_edit_distance_empty_string_dynamic(void);
void test_edit_distance_insertion_dynamic(void);
void test_edit_distance_deletion_dynamic(void);
void test_edit_distance_substitution_dynamic(void);
void test_edit_distance_mixed_operations_dynamic(void);
void test_edit_distance_null_string_dynamic(void);

#endif  // _TEST_EDIT_DISTANCE_H_