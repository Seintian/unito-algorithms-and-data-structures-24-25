#include "../src/algo.h"
#include "../../Resources/C/Unity/unity.h" // Include Unity for CUnit
#include <stdio.h>


void setUp(void) {
    // Code to set up before each test (if needed)
}

void tearDown(void) {
    // Code to clean up after each test (if needed)
}

// DEBUG: This is a test to check if the test is working
void test_example(void) {
    TEST_ASSERT_EQUAL(1, 1);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_example);
    return UNITY_END();
}