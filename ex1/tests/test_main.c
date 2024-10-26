#include "test_algo.h"
#include "test_csv.h"


// SetUp and TearDown functions (are needed by Unity)
void setUp(void) {}
void tearDown(void) {}


int main(void) {
    UNITY_BEGIN();

    // merge_sort tests

    RUN_TEST(test_merge_sort);
    RUN_TEST(test_merge_sort_empty);
    RUN_TEST(test_merge_sort_sorted);
    RUN_TEST(test_merge_sort_reverse_sorted);
    RUN_TEST(test_merge_sort_identical_elements);
    RUN_TEST(test_merge_sort_single_element);
    RUN_TEST(test_merge_sort_negative_numbers);

    // quick_sort tests

    RUN_TEST(test_quick_sort);
    RUN_TEST(test_quick_sort_empty);
    RUN_TEST(test_quick_sort_sorted);
    RUN_TEST(test_quick_sort_reverse_sorted);
    RUN_TEST(test_quick_sort_identical_elements);
    RUN_TEST(test_quick_sort_single_element);
    RUN_TEST(test_quick_sort_negative_numbers);

    // csv tests

    RUN_TEST(test_compare_field1);
    RUN_TEST(test_compare_field2);
    RUN_TEST(test_compare_field3);
    RUN_TEST(test_count_lines);
    RUN_TEST(test_read_records);
    RUN_TEST(test_write_records);

    return UNITY_END();
}
