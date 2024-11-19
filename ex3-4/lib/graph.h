#ifndef _GRAPH_H
#define _GRAPH_H

typedef struct graph *Graph;

typedef struct edge {
    void* source;   // nodo d'origine
    void* dest;     // nodo di destinazione
    void* label;    // etichetta dell'arco

} Edge;

Graph graph_create(
    int labelled,
    int directed,
    int (*compare)(const void*, const void*),
    unsigned long (*hash)(const void*)
);

// crea un grafo vuoto, etichettato se labelled == 1 e diretto se directed == 1,
// le funzioni f1 e f2 sono necessarie per la costruzione della tavola hash che deve essere usata dalla libreria -- O(1)

int graph_is_directed(const Graph gr);                                                           // dice se il grafo è diretto o meno -- O(1)
int graph_is_labelled(const Graph gr);                                                           // dice se il grafo è etichettato o meno -- O(1)
int graph_add_node(Graph gr, const void* node);                                                  // aggiunge un nodo -- O(1)
int graph_add_edge(Graph gr, const void* node1, const void* node2, const void* label);           // aggiunge un arco dati estremi ed etichetta -- O(1) (*)
int graph_contains_node(const Graph gr, const void* node);                                       // controlla se un nodo è nel grafo -- O(1)
int graph_contains_edge(const Graph gr, const void* node1, const void* node2);                   // controlla se un arco è nel grafo -- O(1) (*)
int graph_remove_node(Graph gr, const void* node);                                               // rimuove un nodo dal grafo -- O(N)
int graph_remove_edge(Graph gr, const void* node1, const void* node2);                           // rimuove un arco dal grafo -- O(1) (*)
int graph_num_nodes(const Graph gr);                                                             // numero di nodi -- O(1)
int graph_num_edges(const Graph gr);                                                             // numero di archi -- O(N)
void** graph_get_nodes(const Graph gr);                                                          // recupero dei nodi del grafo -- O(N)
Edge** graph_get_edges(const Graph gr);                                                          // recupero degli archi del grafo -- O(N)
void** graph_get_neighbours(const Graph gr, const void* node);                                   // recupero dei nodi adiacenti ad un dato nodo -- O(1) (*)
int graph_num_neighbours(const Graph gr, const void* node);                                      // recupero del numero di nodi adiacenti ad un dato nodo -- O(1)
void* graph_get_label(const Graph gr, const void* node1, const void* node2);                     // recupero dell'etichetta di un arco -- O(1) (*)
void graph_free(Graph gr);

#endif // _GRAPH_H