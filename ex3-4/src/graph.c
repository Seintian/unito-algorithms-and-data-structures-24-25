#include "graph.h"
#include "hashtable.h" // HashTable's INITIAL_CAPACITY is 2
#include "error_logger.h"
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

int graph_contains_edge(
    const Graph graph,
    const void* node1,
    const void* node2
) {
    if (!graph || !node1 || !node2)
        return RETURN_FAILURE;

    if (
        !hash_table_contains_key(graph -> nodes, node1)
     || !hash_table_contains_key(graph -> nodes, node2)
    )
        return 0;

    const HashTable* edges = (HashTable*) hash_table_get(graph -> nodes, node1);
    if (!edges)
        return RETURN_FAILURE;

    return hash_table_contains_key(edges, node2);
}

int graph_remove_node(Graph graph, const void* node) {
    if (!graph || !node)
        return RETURN_FAILURE;

    if (!hash_table_contains_key(graph -> nodes, node))
        return 0;

    HashTable* node_edges = hash_table_get(graph -> nodes, node);
    if (!node_edges)
        return RETURN_FAILURE;
    
    int removed_edges = free_node_edges(node_edges);
    if (removed_edges == RETURN_FAILURE)
        return RETURN_FAILURE;

    hash_table_remove(graph -> nodes, node);  

    HashTable** all_edges = (HashTable**) hash_table_values(graph -> nodes);
    if (!all_edges)
        return RETURN_FAILURE;
    
    int num_nodes = hash_table_size(graph -> nodes);
    for (int i = 0; i < num_nodes; i++) {
        if (!hash_table_contains_key(all_edges[i], node))
            continue;

        free(hash_table_get(all_edges[i], node));

        hash_table_remove(all_edges[i], node);
        removed_edges++;
    }

    free(all_edges);

    graph -> num_edges -= removed_edges; 

    return 1;
}

int graph_remove_edge(
    Graph graph,
    const void* node1,
    const void* node2
) {
    if (!graph || !node1 || !node2)
        return RETURN_FAILURE;

    if (
        !hash_table_contains_key(graph -> nodes, node1)
     || !hash_table_contains_key(graph -> nodes, node2)
    )
        return 0;

    int result = remove_edge_between_nodes(graph, node1, node2);
    if (result != 1)
        return result;

    graph -> num_edges--;

    if (graph -> directed)
        return 1;
    
    result = remove_edge_between_nodes(graph, node2, node1);
    if (result == 1)
        graph -> num_edges--;
    
    return result;
}

int graph_num_nodes(const Graph graph) {
    if (!graph)
        return -1;

    return hash_table_size(graph -> nodes);
}

int graph_num_edges(const Graph graph) {
    if (!graph)
        return -1;

    return graph -> directed
        ? graph -> num_edges
        : graph -> num_edges / 2;
}

void** graph_get_nodes(const Graph graph) {
    if (!graph)
        return NULL;

    return hash_table_keyset(graph -> nodes);
}

Edge** graph_get_edges(const Graph graph) {
    if (!graph)
        return NULL;

    size_t num_edges = graph_num_edges(graph);
    if (num_edges == 0)
        return NULL;

    Edge** total_edges = (Edge**) malloc(sizeof(Edge*) * num_edges);
    if (!total_edges)
        return NULL;

    HashTable** edges = (HashTable**) hash_table_values(graph -> nodes);
    if (!edges) {
        free(total_edges);
        return NULL;
    }

    int num_nodes = hash_table_size(graph -> nodes);
    size_t k = 0; // control if k >= num_edges should not be necessary
    for (int i = 0; i < num_nodes; i++) {
        int num_neighbours = hash_table_size(edges[i]);
        Edge** neighbours = num_neighbours > 0
                            ? (Edge**) hash_table_values(edges[i])
                            : NULL;
        if (!neighbours && num_neighbours > 0) {
            free(edges);
            free(total_edges);
            return NULL;
        }

        for (size_t j = 0; j < num_neighbours; j++) {
            if (graph -> directed
             || (   !graph -> directed
                 && graph->compare(neighbours[j]->source, neighbours[j]->dest) < 0
                )
            )
                total_edges[k++] = neighbours[j];
        }

        free(neighbours);
    }

    free(edges);

    return total_edges;
}

void** graph_get_neighbours(const Graph graph, const void* node) {
    if (!graph || !node)
        return NULL;
    
    const HashTable* edges = hash_table_get(graph -> nodes, node);
    if (!edges)
        return NULL;

    return hash_table_keyset(edges);
}

int graph_num_neighbours(const Graph graph, const void* node) {
    if (!graph || !node)
        return RETURN_FAILURE;

    const HashTable* edges = hash_table_get(graph -> nodes, node);
    if (!edges)
        return RETURN_FAILURE;

    return hash_table_size(edges);
}

void* graph_get_label(
    const Graph graph,
    const void* node1,
    const void* node2
) {
    if (!graph || !node1 || !node2 || !graph -> labelled)
        return NULL;
    
    const HashTable* edges = hash_table_get(graph -> nodes, node1);
    if (!edges)
        return NULL;

    Edge* edge = hash_table_get(edges, node2);
    if (!edge)
        return NULL;

    return edge -> label;
}

void graph_free(Graph graph) {
    if (!graph) {
        raise_error("graph_free(): graph is NULL.");
        exit(EXIT_FAILURE);
    }

    int num_nodes = hash_table_size(graph -> nodes);
    if (!num_nodes)
        return;

    HashTable** edges = (HashTable**) hash_table_values(graph -> nodes);
    if (!edges) {
        raise_error("graph_free(): unable to allocate memory in order to free graph.");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_nodes; i++) {
        if (free_node_edges(edges[i]) == RETURN_FAILURE) {
            raise_error("graph_free(): unable to allocate memory in order to free graph.");
            exit(EXIT_FAILURE);
        }
    }

    free(edges);
    hash_table_free(graph -> nodes);
    free(graph);
}

static int free_node_edges(HashTable* edges) {
    if (!edges)
        return RETURN_FAILURE;
    
    size_t num_edges = hash_table_size(edges);
    if (num_edges == 0) {
        hash_table_free(edges);
        return 0;
    }

    Edge** edges_array = (Edge**) hash_table_values(edges);
    if (!edges_array)
        return RETURN_FAILURE;

    for (size_t i = 0; i < num_edges; i++)
        free(edges_array[i]);

    free(edges_array);
    hash_table_free(edges);

    return num_edges;
}

static int remove_edge_between_nodes(Graph graph, const void* source, const void* dest) {
    HashTable* edges = hash_table_get(graph->nodes, source);
    if (!edges)
        return RETURN_FAILURE;

    if (!hash_table_contains_key(edges, dest))
        return 0;

    Edge* edge = hash_table_get(edges, dest);
    if (!edge)
        return RETURN_FAILURE;
    free(edge);
    hash_table_remove(edges, dest);

    return 1; 
}

static Edge* edge_create(
    const void* source,
    const void* dest,
    const void* label
) {
    Edge* e = (Edge*) malloc(sizeof(Edge));
    if (!e)
        return NULL;

    e -> source = (void*) source;
    e -> dest = (void*) dest;
    e -> label = (void*) label;

    return e;
}