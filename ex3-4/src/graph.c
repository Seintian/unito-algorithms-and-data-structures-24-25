#include "graph.h"
#include "hashtable.h" // HashTable's INITIAL_CAPACITY is 2
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

/**
 * @brief Frees the memory allocated for the edges of a node in a hash table.
 *
 * This function takes a pointer to a hash table containing edges and frees the
 * memory allocated for the edges of a specific node. It ensures that all
 * resources associated with the edges are properly released to prevent memory
 * leaks.
 *
 * @param edges A pointer to the hash table containing the edges to be freed.
 * @return integer representing the number of the edges freed on success, RETURN_FAILURE on failure.
 */
static int free_node_edges(HashTable* edges);


/**
 * @brief Removes an edge from the graph.
 *
 * This function removes an edge from the graph that connects the node 
 * specified by `source` to the node specified by `dest`.
 *
 * @param graph The graph from which the edge will be removed.
 * @param source A pointer to the source node of the edge.
 * @param dest A pointer to the destination node of the edge.
 * @return integer 1 if the edge was successfully removed, 
 * 0 if the edge was not in the graph, or RETURN_FAILURE on failure.
 */
static int remove_edge_between_nodes(Graph graph, const void* source, const void* dest);

/**
 * @brief Creates a new edge with the given source, destination, and label.
 *
 * This function allocates memory for a new Edge structure and initializes it
 * with the provided source, destination, and label. If memory allocation fails,
 * the function returns NULL.
 *
 * @param source A pointer to the source node of the edge.
 * @param dest A pointer to the destination node of the edge.
 * @param label A pointer to the label of the edge or NULL.
 * @return A pointer to the newly created Edge structure, or NULL if memory
 *         allocation fails.
 */
static Edge* edge_create(const void* source, const void* dest, const void* label);


void** hash_table_values2(const HashTable* table) {
    size_t size = hash_table_size(table);
    if (size == 0) {
        return NULL;
    }

    void** keys = hash_table_keyset(table);
    if (!keys)
        return NULL;

    void** values = (void**) malloc(sizeof(void*) * size);
    if (!values) {
        free(keys);
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        values[i] = hash_table_get(table, keys[i]);
    }

    free(keys);

    return values;
}

struct graph {
    HashTable* nodes;
    bool labelled;
    bool directed;
    int num_edges;
    int (*compare)(const void*, const void*);
    unsigned long (*hash)(const void*);
};

Graph graph_create(
    int labelled,
    int directed,
    int (*compare)(const void*, const void*),
    unsigned long (*hash)(const void*)
) {
    if (!compare || !hash)
        return NULL;

    Graph graph = (Graph) malloc(sizeof(struct graph));
    if (!graph)
        return NULL;

    graph -> nodes = hash_table_create(compare, hash);
    if (!graph -> nodes) {
        free(graph);
        return NULL;
    }

    graph -> labelled = labelled == 1
                        ? true
                        : false;
    graph -> directed = directed == 1
                        ? true
                        : false;
    graph -> num_edges = 0;
    graph -> compare = compare;
    graph -> hash = hash;

    return graph;
}

int graph_is_directed(const Graph graph) {
    if (!graph)
        return RETURN_FAILURE;

    return graph -> directed;
}

int graph_is_labelled(const Graph graph) {
    if (!graph)
        return RETURN_FAILURE;

    return graph -> labelled;
}

int graph_add_node(Graph graph, const void* node) {
    if (!graph || !node)
        return RETURN_FAILURE;

    if (hash_table_contains_key(graph -> nodes, node))
        return 0;

    HashTable* edges = hash_table_create(graph -> compare, graph -> hash);
    if (!edges)
        return RETURN_FAILURE;
    
    hash_table_put(graph -> nodes, node, edges);

    return 1;
}

int graph_add_edge( 
    Graph graph,
    const void* node1,
    const void* node2,
    const void* label
) {
    if (!graph || !node1 || !node2)
        return RETURN_FAILURE;

    HashTable* edges_node1 = (HashTable*) hash_table_get(graph -> nodes, node1);
    if (!edges_node1)
        return RETURN_FAILURE;

    HashTable* edges_node2 = graph->directed
                            ? NULL  
                            : (HashTable*) hash_table_get(graph -> nodes, node2);
    if (!edges_node2 && !graph->directed)
        return RETURN_FAILURE;

    if (
        hash_table_contains_key(edges_node1, node2)
     || (   
            !graph->directed
         && hash_table_contains_key(edges_node2, node1)
        )
    )
        return 0;

    const void* edge_label = graph->labelled
                        ? label
                        : NULL;

    Edge* edge_node1 = edge_create(node1, node2, edge_label);
    if (!edge_node1)
        return RETURN_FAILURE;
    
    Edge* edge_node2 = graph->directed
                            ? NULL  
                            : edge_create(node2, node1, edge_label);
    if (!edge_node2 && !graph->directed) {
        free(edge_node1);

        return RETURN_FAILURE;
    }

    hash_table_put(edges_node1, node2, edge_node1);
    graph -> num_edges++;

    if (graph -> directed)
        return 1;

    hash_table_put(edges_node2, node1, edge_node2);
    graph -> num_edges++;

    return 1;
}

int graph_contains_node(const Graph graph, const void* node) {
    if (!graph || !node)
        return RETURN_FAILURE;

    return hash_table_contains_key(graph -> nodes, node);
}