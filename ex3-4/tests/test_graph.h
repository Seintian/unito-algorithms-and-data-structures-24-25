/**
 * @file test_graph.h
 * @brief Unit test declarations for graph module functions.
 *
 * This file contains the declarations for the unit tests of the graph module. These tests cover various
 * operations and functionalities of the graph data structure, including node and edge management, as well as
 * graph traversal and label retrieval.
 *
 * The graph module is expected to support operations such as:
 * - Creating a graph
 * - Adding and removing nodes and edges
 * - Retrieving neighbors and labels of nodes
 * - Freeing graph memory
 *
 * Each test function is designed to verify the correctness of the respective operation in the graph module.
 *
 * @see graph.h
 */

#ifndef _TEST_GRAPH_H
#define _TEST_GRAPH_H

/**
 * @brief Test case for graph creation.
 *
 * This test verifies the creation of a graph data structure. It ensures that the graph is initialized correctly
 * and that it can handle basic operations such as adding nodes and edges.
 */
void test_graph_creation(void);

/**
 * @brief Test case for adding a node to the graph.
 *
 * This test verifies the functionality of adding a node to the graph. It ensures that nodes can be successfully
 * added and that the graph structure is updated correctly.
 */
void test_graph_add_node(void);

/**
 * @brief Test case for adding an edge to the graph.
 *
 * This test verifies the functionality of adding an edge between two nodes in the graph. It ensures that the edge
 * is correctly added and that the graph structure reflects the new connection between the nodes.
 */
void test_graph_add_edge(void);

/**
 * @brief Test case for removing an edge from the graph.
 *
 * This test verifies the functionality of removing an edge between two nodes in the graph. It ensures that the edge
 * is successfully removed and that the graph structure is updated accordingly.
 */
void test_graph_remove_edge(void);

/**
 * @brief Test case for removing a node from the graph.
 *
 * This test verifies the functionality of removing a node from the graph. It ensures that the node is removed correctly
 * and that all associated edges are also removed.
 */
void test_graph_remove_node(void);

/**
 * @brief Test case for retrieving neighbors of a node.
 *
 * This test verifies the functionality of retrieving the neighbors of a node in the graph. It ensures that the correct
 * set of neighboring nodes is returned.
 */
void test_graph_get_neighbours(void);

/**
 * @brief Test case for retrieving the label of a node.
 *
 * This test verifies the functionality of retrieving the label of a node in the graph. It ensures that the correct label
 * is returned for a given node.
 */
void test_graph_get_label(void);

/**
 * @brief Test case for freeing the graph.
 *
 * This test verifies the functionality of freeing the graph's memory. It ensures that all memory associated with the
 * graph is properly released when the graph is freed.
 */
void test_graph_free(void);

/**
 * @brief Test case for a complex graph scenario.
 *
 * This test verifies the functionality of the graph in a more complex scenario, involving multiple nodes, edges,
 * and various operations. It ensures that the graph handles complex cases correctly.
 */
void test_graph_complex(void);

/**
 * @brief Test case for exhaustive graph memory freeing.
 *
 * This test verifies the functionality of freeing the graph's memory in an exhaustive manner. It ensures that all memory
 * allocations are properly freed and that no memory leaks occur.
 */
void test_graph_free_exhaustive(void);

#endif // _TEST_GRAPH_H
