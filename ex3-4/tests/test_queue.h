/**
 * @file test_queue.h
 * @brief Header file for testing queue functions.
 * 
 * This file contains declarations for functions used to test
 * the functionality of the queue data structure. It includes tests
 * for creating a queue, checking if the queue is empty, enqueuing
 * and dequeuing elements, and freeing the queue.
 * 
 * @see queue.h
 */

#ifndef _TEST_QUEUE_H
#define _TEST_QUEUE_H

/**
 * @brief Test the creation of a queue.
 * 
 * This function tests the functionality of creating a queue,
 * ensuring that it is initialized correctly and is ready for use.
 */
void test_queue_create();

/**
 * @brief Test if the queue is empty.
 * 
 * This function tests the queue's ability to correctly identify
 * whether it is empty or not.
 */
void test_queue_is_empty();

/**
 * @brief Test the enqueue and dequeue operations.
 * 
 * This function tests the enqueue and dequeue operations of the
 * queue, ensuring that elements are added and removed correctly
 * while maintaining the correct order.
 */
void test_queue_enqueue_dequeue();

/**
 * @brief Test the freeing of the queue.
 * 
 * This function tests the functionality of freeing the memory
 * associated with the queue, ensuring that resources are released
 * correctly.
 */
void test_queue_free();

#endif // _TEST_QUEUE_H
