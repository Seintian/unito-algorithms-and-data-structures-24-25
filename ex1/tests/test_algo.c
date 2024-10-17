#include "../src/algo.h"
#include "../../Resources/C/Unity/unity.h" // Include Unity
#include <stdio.h>


int int_cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

void setUp(void) {
    // Code to set up before each test (if needed)
}

void tearDown(void) {
    // Code to clean up after each test (if needed)
}

void test_merge_sort(void) {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {5, 6, 7, 11, 12, 13};

    merge_sort(arr, n, sizeof(int), int_cmp);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, n);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_merge_sort);

    return UNITY_END();
}