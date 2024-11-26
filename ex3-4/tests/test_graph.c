#include "graph.h"
#include "test_graph.h"
#include "unity.h"
#include <stdlib.h>
#include <string.h>

// Helper functions for tests
static int compare_ints(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

static unsigned long hash_ints(const void* key) {
    return (unsigned long)(*(int*)key);
}

void test_graph_create() {
    Graph graph = graph_create(1, 1, compare_ints, hash_ints);
    TEST_ASSERT_NOT_NULL(graph);
    TEST_ASSERT_EQUAL(1, graph_is_directed(graph));
    TEST_ASSERT_EQUAL(1, graph_is_labelled(graph));
    graph_free(graph);
}

void test_graph_add_node() {
    Graph graph = graph_create(0, 0, compare_ints, hash_ints);
    int node = 1;

    TEST_ASSERT_EQUAL(1, graph_add_node(graph, &node));
    TEST_ASSERT_EQUAL(0, graph_add_node(graph, &node)); // Duplicate node
    TEST_ASSERT_EQUAL(1, graph_contains_node(graph, &node));

    graph_free(graph);
}

void test_graph_add_edge() {
    Graph graph = graph_create(1, 1, compare_ints, hash_ints);
    int node1 = 1, node2 = 2, label = 100;

    graph_add_node(graph, &node1);
    graph_add_node(graph, &node2);

    TEST_ASSERT_EQUAL(1, graph_add_edge(graph, &node1, &node2, &label));
    TEST_ASSERT_EQUAL(0, graph_add_edge(graph, &node1, &node2, &label)); // Duplicate edge
    TEST_ASSERT_EQUAL(1, graph_contains_edge(graph, &node1, &node2));

    graph_free(graph);
}

void test_graph_contains_node() {
    Graph graph = graph_create(0, 0, compare_ints, hash_ints);
    int node = 1;

    TEST_ASSERT_EQUAL(0, graph_contains_node(graph, &node));
    graph_add_node(graph, &node);
    TEST_ASSERT_EQUAL(1, graph_contains_node(graph, &node));

    graph_free(graph);
}

void test_graph_contains_edge() {
    Graph graph = graph_create(0, 1, compare_ints, hash_ints);
    int node1 = 1, node2 = 2, label = 100;

    graph_add_node(graph, &node1);
    graph_add_node(graph, &node2);

    TEST_ASSERT_EQUAL(0, graph_contains_edge(graph, &node1, &node2));
    graph_add_edge(graph, &node1, &node2, &label);
    TEST_ASSERT_EQUAL(1, graph_contains_edge(graph, &node1, &node2));

    graph_free(graph);
}

void test_graph_remove_node() {
    Graph graph = graph_create(0, 0, compare_ints, hash_ints);
    int node = 1;

    graph_add_node(graph, &node);
    TEST_ASSERT_EQUAL(1, graph_remove_node(graph, &node));
    TEST_ASSERT_EQUAL(0, graph_remove_node(graph, &node));

    graph_free(graph);
}

void test_graph_remove_edge() {
    Graph graph = graph_create(1, 1, compare_ints, hash_ints);
    int node1 = 1, node2 = 2, label = 100;

    graph_add_node(graph, &node1);
    graph_add_node(graph, &node2);
    graph_add_edge(graph, &node1, &node2, &label);

    TEST_ASSERT_EQUAL(1, graph_remove_edge(graph, &node1, &node2));
    TEST_ASSERT_EQUAL(0, graph_remove_edge(graph, &node1, &node2));

    graph_free(graph);
}

void test_graph_get_nodes() {
    Graph graph = graph_create(0, 0, compare_ints, hash_ints);
    int node1 = 1, node2 = 2;

    graph_add_node(graph, &node1);
    graph_add_node(graph, &node2);

    void** nodes = graph_get_nodes(graph);
    TEST_ASSERT_NOT_NULL(nodes);
    TEST_ASSERT_EQUAL(2, graph_num_nodes(graph));

    free(nodes);
    graph_free(graph);
}

void test_graph_get_edges() {
    Graph graph = graph_create(1, 1, compare_ints, hash_ints);
    int node1 = 1, node2 = 2, label = 100;

    graph_add_node(graph, &node1);
    graph_add_node(graph, &node2);
    graph_add_edge(graph, &node1, &node2, &label);

    Edge** edges = graph_get_edges(graph);
    TEST_ASSERT_NOT_NULL(edges);
    TEST_ASSERT_EQUAL(1, graph_num_edges(graph));
    TEST_ASSERT_EQUAL(&node1, edges[0]->source);
    TEST_ASSERT_EQUAL(&node2, edges[0]->dest);

    free(edges);
    graph_free(graph);
}

void test_graph_get_neighbours() {
    Graph graph = graph_create(1, 1, compare_ints, hash_ints);
    int node1 = 1, node2 = 2, label = 100;

    graph_add_node(graph, &node1);
    graph_add_node(graph, &node2);
    graph_add_edge(graph, &node1, &node2, &label);

    void** neighbours = graph_get_neighbours(graph, &node1);
    TEST_ASSERT_NOT_NULL(neighbours);
    TEST_ASSERT_EQUAL(1, graph_num_neighbours(graph, &node1));
    TEST_ASSERT_EQUAL(&node2, neighbours[0]);

    free(neighbours);
    graph_free(graph);
}

void test_graph_get_label() {
    Graph graph = graph_create(1, 1, compare_ints, hash_ints);
    int node1 = 1, node2 = 2, label = 100;

    graph_add_node(graph, &node1);
    graph_add_node(graph, &node2);
    graph_add_edge(graph, &node1, &node2, &label);

    TEST_ASSERT_EQUAL(&label, graph_get_label(graph, &node1, &node2));

    graph_free(graph);
}

void test_graph_num_nodes() {
    Graph graph = graph_create(0, 0, compare_ints, hash_ints);
    int node1 = 1, node2 = 2;

    graph_add_node(graph, &node1);
    graph_add_node(graph, &node2);

    TEST_ASSERT_EQUAL(2, graph_num_nodes(graph));

    graph_free(graph);
}

void test_graph_num_edges() {
    Graph graph = graph_create(1, 1, compare_ints, hash_ints);
    int node1 = 1, node2 = 2, label = 100;

    graph_add_node(graph, &node1);
    graph_add_node(graph, &node2);
    graph_add_edge(graph, &node1, &node2, &label);

    TEST_ASSERT_EQUAL(1, graph_num_edges(graph));

    graph_free(graph);
}

void test_graph_free() {
    Graph graph = graph_create(1, 1, compare_ints, hash_ints);
    int node1 = 1, node2 = 2, label = 100;

    graph_add_node(graph, &node1);
    graph_add_node(graph, &node2);
    graph_add_edge(graph, &node1, &node2, &label);

    graph_free(graph);
    TEST_PASS();
}
