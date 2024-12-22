/**
 * @file test_main.c
 * @brief Main entry point for running unit tests on graph, queue, and IO library functionality.
 * 
 * This file serves as the entry point for running unit tests using the Unity test framework.
 * It includes tests for graph operations (creation, addition/removal of nodes and edges, etc.),
 * queue operations (creation, enqueue/dequeue, etc.), and IO library functions (reading records,
 * writing output). Each test is run using the `RUN_TEST` macro provided by Unity.
 * 
 * @note The `setUp` and `tearDown` functions are required by Unity but are empty in this file.
 * 
 * @see test_graph.h
 * @see test_queue.h
 * @see test_io_lib.h
 * @see Unity
 */

#include "test_graph.h"
#include "test_queue.h"
#include "test_io_lib.h"
#include "unity.h"

/**
 * @brief Set up the test environment.
 * 
 * This function is called before each test to set up any necessary
 * resources or configurations. It is executed automatically by the Unity
 * test framework.
 */
void setUp(void) {
    // set stuff up here
}

/**
 * @brief Clean up the test environment.
 * 
 * This function is called after each test to clean up any resources
 * or configurations that were set up in the setUp function. It is
 * executed automatically by the Unity test framework.
 */
void tearDown(void) {
    // clean stuff up here
}

/**
 * @brief Main function for running all tests.
 * 
 * This function initializes the Unity test framework, runs the tests for
 * graph, queue, and IO library functionality, and then concludes the test
 * execution. It returns the result of the Unity test run.
 * 
 * @return The result of the Unity test execution.
 */
int main(void) {
    UNITY_BEGIN();  /**< Initialize Unity test framework */

    // Graph tests
    RUN_TEST(test_graph_creation);  /**< Test the creation of a graph */
    RUN_TEST(test_graph_add_node);  /**< Test adding a node to the graph */
    RUN_TEST(test_graph_add_edge);  /**< Test adding an edge to the graph */
    RUN_TEST(test_graph_remove_edge);  /**< Test removing an edge from the graph */
    RUN_TEST(test_graph_remove_node);  /**< Test removing a node from the graph */
    RUN_TEST(test_graph_get_neighbours);  /**< Test getting neighbors of a node */
    RUN_TEST(test_graph_get_label);  /**< Test getting the label of a node */
    RUN_TEST(test_graph_free);  /**< Test freeing the graph */
    RUN_TEST(test_graph_complex);  /**< Test complex graph operations */
    RUN_TEST(test_graph_free_exhaustive);  /**< Test exhaustive graph freeing */

    // Queue tests
    RUN_TEST(test_queue_create);  /**< Test the creation of a queue */
    RUN_TEST(test_queue_is_empty);  /**< Test checking if the queue is empty */
    RUN_TEST(test_queue_enqueue_dequeue);  /**< Test enqueue and dequeue operations */
    RUN_TEST(test_queue_free);  /**< Test freeing the queue */

    // IO Lib tests
    RUN_TEST(test_read_records);  /**< Test reading records from a file */
    RUN_TEST(test_write_output);  /**< Test writing output to a file */

    return UNITY_END();  /**< End the Unity test framework and return the result */
}
