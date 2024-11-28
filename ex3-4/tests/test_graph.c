#include "graph.h"
#include "test_graph.h"
#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Utility function to create a string node
char* create_node(const char* name) {
    char* node = malloc(strlen(name) + 1);
    strcpy(node, name);
    return node;
}

// Utility function to create a string label
char* create_label(const char* label) {
    char* lbl = malloc(strlen(label) + 1);
    strcpy(lbl, label);
    return lbl;
}

// Utility function to free nodes and labels
void free_node(void* node) {
    free(node);
}

void free_label(void* label) {
    free(label);
}

// Comparison function for nodes
int compare_nodes(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

// Hash function for nodes
unsigned long hash_node(const void* key) {
    const char* str = (const char*)key;
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

void test_graph_creation(void) {
    Graph graph = graph_create(1, 1, compare_nodes, hash_node);
    TEST_ASSERT_NOT_NULL(graph);
    TEST_ASSERT_EQUAL(1, graph_is_labelled(graph));
    TEST_ASSERT_EQUAL(1, graph_is_directed(graph));
    TEST_ASSERT_EQUAL(0, graph_num_nodes(graph));
    TEST_ASSERT_EQUAL(0, graph_num_edges(graph));
    graph_free(graph);
}

void test_graph_add_node(void) {
    Graph graph = graph_create(1, 1, compare_nodes, hash_node);
    char* node1 = create_node("Node1");
    char* node2 = create_node("Node2");

    TEST_ASSERT_EQUAL(1, graph_add_node(graph, node1));
    TEST_ASSERT_EQUAL(1, graph_add_node(graph, node2));
    TEST_ASSERT_EQUAL(2, graph_num_nodes(graph));
    TEST_ASSERT_EQUAL(1, graph_contains_node(graph, node1));
    TEST_ASSERT_EQUAL(1, graph_contains_node(graph, node2));

    graph_free(graph);
    free_node(node1);
    free_node(node2);
}

void test_graph_add_edge(void) {
    Graph graph = graph_create(1, 1, compare_nodes, hash_node);
    char* node1 = create_node("Node1");
    char* node2 = create_node("Node2");
    char* label = create_label("Label");

    graph_add_node(graph, node1);
    graph_add_node(graph, node2);

    TEST_ASSERT_EQUAL(1, graph_add_edge(graph, node1, node2, label));
    TEST_ASSERT_EQUAL(1, graph_num_edges(graph));
    TEST_ASSERT_EQUAL(1, graph_contains_edge(graph, node1, node2));

    graph_free(graph);
    free_node(node1);
    free_node(node2);
    free_label(label);
}

void test_graph_remove_edge(void) {
    Graph graph = graph_create(1, 1, compare_nodes, hash_node);
    char* node1 = create_node("Node1");
    char* node2 = create_node("Node2");
    char* label = create_label("Label");

    graph_add_node(graph, node1);
    graph_add_node(graph, node2);
    graph_add_edge(graph, node1, node2, label);

    TEST_ASSERT_EQUAL(1, graph_remove_edge(graph, node1, node2));
    TEST_ASSERT_EQUAL(0, graph_num_edges(graph));
    TEST_ASSERT_EQUAL(0, graph_contains_edge(graph, node1, node2));

    graph_free(graph);
    free_node(node1);
    free_node(node2);
    free_label(label);
}

void test_graph_remove_node(void) {
    Graph graph = graph_create(1, 1, compare_nodes, hash_node);
    char* node1 = create_node("Node1");
    char* node2 = create_node("Node2");
    char* label = create_label("Label");

    graph_add_node(graph, node1);
    graph_add_node(graph, node2);
    graph_add_edge(graph, node1, node2, label);

    TEST_ASSERT_EQUAL(1, graph_remove_node(graph, node1));
    TEST_ASSERT_EQUAL(1, graph_num_nodes(graph));
    TEST_ASSERT_EQUAL(0, graph_num_edges(graph));
    TEST_ASSERT_EQUAL(0, graph_contains_node(graph, node1));
    TEST_ASSERT_EQUAL(1, graph_contains_node(graph, node2));

    graph_free(graph);
    free_node(node1);
    free_node(node2);
    free_label(label);
}

void test_graph_get_neighbours(void) {
    Graph graph = graph_create(1, 1, compare_nodes, hash_node);
    char* node1 = create_node("Node1");
    char* node2 = create_node("Node2");
    char* label = create_label("Label");

    graph_add_node(graph, node1);
    graph_add_node(graph, node2);
    graph_add_edge(graph, node1, node2, label);

    void** neighbours = graph_get_neighbours(graph, node1);
    int num_neighbours = graph_num_neighbours(graph, node1);
    TEST_ASSERT_EQUAL(1, num_neighbours);
    TEST_ASSERT_EQUAL_STRING("Node2", (const char*)neighbours[0]);

    free(neighbours);
    graph_free(graph);
    free_node(node1);
    free_node(node2);
    free_label(label);
}

void test_graph_get_label(void) {
    Graph graph = graph_create(1, 1, compare_nodes, hash_node);
    char* node1 = create_node("Node1");
    char* node2 = create_node("Node2");
    char* label = create_label("Label");

    graph_add_node(graph, node1);
    graph_add_node(graph, node2);
    graph_add_edge(graph, node1, node2, label);

    const void* edge_label = graph_get_label(graph, node1, node2);
    TEST_ASSERT_NOT_NULL(edge_label);
    TEST_ASSERT_EQUAL_STRING("Label", (const char*)edge_label);

    graph_free(graph);
    free_node(node1);
    free_node(node2);
    free_label(label);
}

void test_graph_free(void) {
    Graph graph = graph_create(1, 1, compare_nodes, hash_node);
    char* node1 = create_node("Node1");
    char* node2 = create_node("Node2");
    char* label = create_label("Label");

    graph_add_node(graph, node1);
    graph_add_node(graph, node2);
    graph_add_edge(graph, node1, node2, label);

    graph_free(graph);

    free_node(node1);
    free_node(node2);
    free_label(label);
}

void test_graph_complex(void) {
    Graph graph = graph_create(1, 0, compare_nodes, hash_node);
    char* node1 = create_node("Node1");
    char* node2 = create_node("Node2");
    char* node3 = create_node("Node3");
    char* label1 = create_label("Label1");
    char* label2 = create_label("Label2");

    graph_add_node(graph, node1);
    graph_add_node(graph, node2);
    graph_add_node(graph, node3);
    graph_add_edge(graph, node1, node2, label1);
    graph_add_edge(graph, node2, node3, label2);

    TEST_ASSERT_EQUAL(3, graph_num_nodes(graph));
    TEST_ASSERT_EQUAL(2, graph_num_edges(graph));

    graph_remove_edge(graph, node1, node2);
    TEST_ASSERT_EQUAL(1, graph_num_edges(graph));

    graph_remove_node(graph, node2);
    TEST_ASSERT_EQUAL(2, graph_num_nodes(graph));
    TEST_ASSERT_EQUAL(0, graph_num_edges(graph));

    graph_free(graph);
    free_node(node1);
    free_node(node2);
    free_node(node3);
    free_label(label1);
    free_label(label2);
}

void test_graph_free_exhaustive(void) {
    Graph graph = graph_create(1, 1, compare_nodes, hash_node);
    TEST_ASSERT_NOT_NULL(graph);

    // Add a large number of nodes
    const int num_nodes = 1000;
    char* nodes[num_nodes];
    for (int i = 0; i < num_nodes; i++) {
        char name[20];
        sprintf(name, "Node%d", i);
        nodes[i] = create_node(name);
        TEST_ASSERT_EQUAL(1, graph_add_node(graph, nodes[i]));
    }
    TEST_ASSERT_EQUAL(num_nodes, graph_num_nodes(graph));

    // Add edges between nodes
    int expected_edges = 0;
    for (int i = 0; i < num_nodes; i++) {
        for (int j = i + 1; j < num_nodes; j++) {
            char label[20];
            sprintf(label, "Label%d-%d", i, j);
            char* edge_label = create_label(label);
            TEST_ASSERT_EQUAL(1, graph_add_edge(graph, nodes[i], nodes[j], edge_label));
            free_label(edge_label); // Free label after adding edge
            expected_edges++;
        }
    }
    TEST_ASSERT_EQUAL(expected_edges, graph_num_edges(graph));

    // Remove some edges
    for (int i = 0; i < num_nodes; i += 2) {
        for (int j = i + 1; j < num_nodes; j += 2) {
            if (graph_contains_edge(graph, nodes[i], nodes[j])) {
                TEST_ASSERT_EQUAL(1, graph_remove_edge(graph, nodes[i], nodes[j]));
                expected_edges--;
            }
        }
    }
    TEST_ASSERT_EQUAL(expected_edges, graph_num_edges(graph));

    // Remove some nodes
    int expected_nodes = num_nodes;
    for (int i = 0; i < num_nodes; i += 3) {
        if (graph_contains_node(graph, nodes[i])) {
            TEST_ASSERT_EQUAL(1, graph_remove_node(graph, nodes[i]));
            expected_nodes--;
        }
    }
    TEST_ASSERT_EQUAL(expected_nodes, graph_num_nodes(graph));

    // Check that the nodes returned are correct after removal
    char** nodes_returned = (char**)graph_get_nodes(graph);
    TEST_ASSERT_NOT_NULL(nodes_returned);
    int returned_count = 0;
    for (int i = 0; i < num_nodes; i++) {
        if (i % 3 == 0) 
            continue;
        int found = 0;
        for (int j = 0; j < expected_nodes; j++) {
            if (compare_nodes(nodes[i], nodes_returned[j]) == 0) {
                found = 1;
                break;
            }
        }
        TEST_ASSERT_EQUAL(1, found);
        returned_count++;
    }
    TEST_ASSERT_EQUAL(expected_nodes, returned_count);
    free(nodes_returned);

    /*Edge** edges = (Edge**)graph_get_edges(graph);
    free(edges[0]);*/
    
    // Free the graph
    graph_free(graph);

    // Free nodes
    for (int i = 0; i < num_nodes; i++) {
        free_node(nodes[i]);
    }

    printf("test_graph_free_exhaustive passed\n");
}