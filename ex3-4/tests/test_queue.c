/**
 * @file test_queue.c
 * @brief Unit tests for the queue data structure using the Unity framework.
 * 
 * This source file contains the implementation of unit tests for the queue data structure.
 */

#include "test_queue.h"
#include "unity.h"
#include "queue.h"


/**
 * @brief Test the creation of a queue.
 * 
 * This function tests the functionality of creating a queue,
 * ensuring that it is initialized correctly and is empty at the start.
 */
void test_queue_create(void) {
    Queue q = queue_create();
    TEST_ASSERT_NOT_NULL(q);  /**< Ensure the queue is not NULL */
    TEST_ASSERT_EQUAL(1, queue_is_empty(q));  /**< Ensure the queue is empty initially */
    queue_free(q);  /**< Free the queue after the test */
}

/**
 * @brief Test if the queue is empty.
 * 
 * This function tests the queue's ability to correctly identify
 * whether it is empty or not, both before and after enqueuing an element.
 */
void test_queue_is_empty(void) {
    Queue q = queue_create();
    TEST_ASSERT_EQUAL(1, queue_is_empty(q));  /**< Ensure the queue is empty initially */
    
    int data = 42;
    queue_enqueue(q, &data);  /**< Enqueue an element */
    TEST_ASSERT_EQUAL(0, queue_is_empty(q));  /**< Ensure the queue is not empty after enqueueing */
    
    queue_free(q);  /**< Free the queue after the test */
}

/**
 * @brief Test the enqueue and dequeue operations.
 * 
 * This function tests the enqueue and dequeue operations of the
 * queue, ensuring that elements are added and removed correctly
 * while maintaining the correct order.
 */
void test_queue_enqueue_dequeue(void) {
    Queue q = queue_create();
    int data1 = 42, data2 = 84;
    
    TEST_ASSERT_EQUAL(RETURN_SUCCESS, queue_enqueue(q, &data1));  /**< Enqueue the first element */
    TEST_ASSERT_EQUAL(RETURN_SUCCESS, queue_enqueue(q, &data2));  /**< Enqueue the second element */
    
    TEST_ASSERT_EQUAL_PTR(&data1, queue_first(q));  /**< Ensure the first element is data1 */
    TEST_ASSERT_EQUAL_PTR(&data1, queue_dequeue(q));  /**< Dequeue the first element and check if it's data1 */
    
    TEST_ASSERT_EQUAL_PTR(&data2, queue_first(q));  /**< Ensure the first element is now data2 */
    TEST_ASSERT_EQUAL_PTR(&data2, queue_dequeue(q));  /**< Dequeue the second element and check if it's data2 */
    
    TEST_ASSERT_EQUAL(1, queue_is_empty(q));  /**< Ensure the queue is empty after dequeuing all elements */
    
    queue_free(q);  /**< Free the queue after the test */
}

/**
 * @brief Test the freeing of the queue.
 * 
 * This function tests the functionality of freeing the memory
 * associated with the queue, ensuring that resources are released
 * correctly.
 */
void test_queue_free(void) {
    Queue q = queue_create();
    TEST_ASSERT_EQUAL(RETURN_SUCCESS, queue_free(q));  /**< Ensure the queue is freed successfully */
    TEST_ASSERT_EQUAL(RETURN_FAILURE, queue_free(NULL));  /**< Ensure freeing a NULL queue returns failure */
}
