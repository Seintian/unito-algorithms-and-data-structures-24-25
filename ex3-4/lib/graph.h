#ifndef _GRAPH_H
#define _GRAPH_H

typedef struct graph *Graph;

/**
 * @struct edge
 * @brief Represents an edge in a graph.
 *
 * @var edge::source
 * Pointer to the source node of the edge.
 * @var edge::dest
 * Pointer to the destination node of the edge.
 * @var edge::label
 * Pointer to an optional label for the edge.
 */
typedef struct edge {
    void* source;   
    void* dest;     
    void* label;    
} Edge;

/**
 * @brief Creates an empty graph.
 *
 * This function initializes an empty graph. The graph can be either labelled or unlabelled,
 * and either directed or undirected, based on the parameters provided.
 *
 * @param labelled If set to 1, the graph will be labelled. If set to 0, the graph will be unlabelled.
 * @param directed If set to 1, the graph will be directed. If set to 0, the graph will be undirected.
 * @param compare A pointer to a function that compares two elements. This function is necessary for
 *                constructing the hash table used by the library.
 * @param hash A pointer to a function that computes the hash value of an element. This function is
 *             necessary for constructing the hash table used by the library.
 *
 * @return A new Graph instance, or NULL on failure.
 */
Graph graph_create(
    int labelled,
    int directed,
    int (*compare)(const void*, const void*),
    unsigned long (*hash)(const void*)
);

/**
 * @brief Checks if the graph is directed.
 * 
 * @param gr The graph to check.
 * @return integer 1 if the graph is directed, 0 if it is not directed, RETURN_FAILURE on failure.
 */
int graph_is_directed(const Graph gr);

/**
 * @brief Checks if the graph is labelled.
 * 
 * @param gr The graph to check.
 * @return integer 1 if the graph is labelled, 0 if it is not labelled, RETURN_FAILURE on failure.
 */
int graph_is_labelled(const Graph gr);

/**
 * @brief Adds a node to the graph.
 * 
 * @param gr The graph to which the node will be added.
 * @param node The node to add.
 * @return integer 1 if the node is added, 0 if the node is already in the graph, RETURN_FAILURE on failure.
 */
int graph_add_node(Graph gr, const void* node);

/**
 * @brief Adds an edge between two nodes in the graph.
 * 
 * @param gr The graph to which the edge will be added.
 * @param node1 The first node, and also the source node, if gr graph is not directed.
 * @param node2 The second node, and also the destination node, if gr graph is not directed.
 * @param label The label for the edge (can be NULL if the graph is not labelled).
 * @return integer 1 if the edge is added, 0 if the edge is already in the graph, RETURN_FAILURE on failure.
 */
int graph_add_edge(Graph gr, const void* node1, const void* node2, const void* label);

/**
 * @brief Checks if the graph contains a specific node.
 * 
 * @param gr The graph to check.
 * @param node The node to check for.
 * @return integer 1 if the node is in the graph, 0 if the node is not in the graph, RETURN_FAILURE on failure.
 */
int graph_contains_node(const Graph gr, const void* node);

/**
 * @brief Checks if the graph contains an edge between two nodes.
 * 
 * @param gr The graph to check.
 * @param node1 The first node, and also the source node, if gr graph is not directed.
 * @param node2 The second node, and also the destination node, if gr graph is not directed.
 * @return integer 1 if the edge is in the graph, 0 if the edge is not in the graph, RETURN_FAILURE on failure.
 */
int graph_contains_edge(const Graph gr, const void* node1, const void* node2);

/**
 * @brief Removes a node from the graph.
 * 
 * @param gr The graph from which the node will be removed.
 * @param node The node to remove.
 * @return integer 1 if the node is removed, 0 if the node is not in the graph, RETURN_FAILURE on failure.
 */
int graph_remove_node(Graph gr, const void* node);

/**
 * @brief Removes an edge between two nodes in the graph.
 * 
 * @param gr The graph from which the edge will be removed.
 * @param node1 The first node, and also the source node, if gr graph is not directed.
 * @param node2 The second node, and also the destination node, if gr graph is not directed.
 * @return integer 1 if the edge is removed, 0 if the edge is not in the graph, RETURN_FAILURE on failure.
 */
int graph_remove_edge(Graph gr, const void* node1, const void* node2);

/**
 * @brief Gets the number of nodes in the graph.
 * 
 * @param gr The graph to check.
 * @return integer representing the number of nodes in the graph, RETURN_FAILURE on failure.
 */
int graph_num_nodes(const Graph gr);

/**
 * @brief Gets the number of edges in the graph.
 * 
 * @param gr The graph to check.
 * @return integer representing the number of edges in the graph, or RETURN_FAILURE on failure.
 */
int graph_num_edges(const Graph gr);

/**
 * @brief Gets all the nodes in the graph.
 * 
 * @param gr The graph to get nodes from.
 * @return void** representing an array of pointers to the nodes in the graph, or NULL on failure.
 */
void** graph_get_nodes(const Graph gr);

/**
 * @brief Gets all the edges in the graph.
 * 
 * @param gr The graph to get edges from.
 * @return Edge** representing an array of pointers to the edges in the graph, or NULL on failure.
 */
Edge** graph_get_edges(const Graph gr);

/**
 * @brief Gets all the neighbours of a specific node in the graph.
 * 
 * @param gr The graph to check.
 * @param node The node to get neighbours for.
 * @return void** representing an array of pointers to the neighbours of node, NULL if node is not in the graph, or on failure.
 */
void** graph_get_neighbours(const Graph gr, const void* node);

/**
 * @brief Gets the number of neighbours of a specific node in the graph.
 * 
 * @param gr The graph to check.
 * @param node The node to get the number of neighbours for.
 * @return integer representing the number of neighbours of node, RETURN_FAILURE if node is not in the graph, or on failure.
 */
int graph_num_neighbours(const Graph gr, const void* node);

/**
 * @brief Gets the label of an edge between two nodes in the graph.
 * 
 * @param gr The graph to check.
 * @param node1 The first node, and also the source node, if gr graph is not directed.
 * @param node2 The second node, and also the destination node, if gr graph is not directed.
 * @return void* representing the label of the edge, or NULL if the edge does not exist or the graph is not labelled.
 */
void* graph_get_label(const Graph gr, const void* node1, const void* node2);

/**
 * @brief Frees the memory allocated for the graph.
 * 
 * @param gr The graph to free.
 */
void graph_free(Graph gr);

#endif // _GRAPH_H