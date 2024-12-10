#include "graph.h"
#include "hashtable.h"
#include "queue.h"
#include "io_lib.h"
#include "error_logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Helper function for breadth_first_visit() which releases resources used in the function.
 *
 * This function frees the memory allocated for the BFS queue, the explored set hash table,
 * and the array of visited nodes.
 *
 * @param bfs_queue The queue used in the BFS algorithm.
 * @param explored_set The hash table containing the set of explored nodes.
 * @param visited_nodes The array of pointers to visited nodes.
 */
void bfs_cleanup(Queue bfs_queue, HashTable* explored_set, void** visited_nodes) {
    queue_free(bfs_queue);
    hash_table_free(explored_set);
    free(visited_nodes);
}

/**
 * @brief Performs a breadth-first search (BFS) traversal on a graph starting from a given node.
 *
 * This function visits all nodes in the graph reachable from the start node using BFS and returns
 * an array of pointers to the visited nodes in the order they were visited. 
 *
 * @param gr The graph to traverse.
 * @param start The starting node for the BFS traversal.
 * @param compare A function pointer to compare two nodes.
 * @param hash A function pointer to compute the hash value of a node.
 * @return A NULL-terminated array of pointers to the visited nodes, or NULL on failure.
 *
 * @note The caller is responsible for freeing the returned array.
 *
 * @details The function handles the following error cases:
 * - If any of the input parameters are NULL, the function returns NULL.
 * - If the start node is not present in the graph, the function returns NULL.
 * - If memory allocation fails at any point, the function returns NULL.
 * - If queue or hash table operations fail, the function returns NULL.
 */
void** breadth_first_visit(Graph gr, void* start, int (*compare)(const void*, const void*), unsigned long (*hash)(const void*)) {
    if (!gr || !start || !compare || !hash)
        return NULL;
    
    if (!graph_contains_node(gr, start))
        return NULL;
    
    void** visited_nodes = malloc(sizeof(void*) * (graph_num_nodes(gr) + 1)); // non necessario controllo su output di graph_num_nodes
    if (!visited_nodes)
        return NULL;
    
    size_t visited_nodes_count = 1;

    Queue bfs_queue = queue_create();
    if (!bfs_queue) {
        free(visited_nodes);
        return NULL;
    }

    HashTable* explored_set = hash_table_create(compare, hash);
    if (!explored_set) {
        bfs_cleanup(bfs_queue, NULL, visited_nodes);
        return NULL;
    }

    if (queue_enqueue(bfs_queue, start) == RETURN_FAILURE) {
        bfs_cleanup(bfs_queue, explored_set, visited_nodes);
        return NULL;
    }
    
    hash_table_put(explored_set, start, NULL);
    visited_nodes[0] = start;

    while (!queue_is_empty(bfs_queue)) {
        const void* current_node = queue_dequeue(bfs_queue); // non necessario controllo su output di queue_dequeue
        void** neighbours = graph_get_neighbours(gr, current_node);
        int num_neighbours = graph_num_neighbours(gr, current_node);
        if (!neighbours && num_neighbours > 0) { 
            bfs_cleanup(bfs_queue, explored_set, visited_nodes);
            return NULL;
        }

        for(size_t i = 0; i < num_neighbours; i++) {
            if (hash_table_contains_key(explored_set, neighbours[i]))
                continue;

            if (queue_enqueue(bfs_queue, neighbours[i]) == RETURN_FAILURE) {
                bfs_cleanup(bfs_queue, explored_set, visited_nodes);
                free(neighbours);
                return NULL;
            }

            hash_table_put(explored_set, neighbours[i], NULL);
            visited_nodes[visited_nodes_count++] = neighbours[i];
        }

        free(neighbours);
    }

    visited_nodes[visited_nodes_count] = NULL;
    void** tmp = visited_nodes;
    visited_nodes = realloc(visited_nodes, sizeof(void*) * (visited_nodes_count + 1));

    bfs_cleanup(bfs_queue, explored_set, NULL);

    return visited_nodes ? visited_nodes : tmp;
}

/**
 * @brief Validates the input arguments.
 *
 * This function validates the input arguments of the program.
 * It checks if the dist_csv_path and output_file files are different,
 * if the dist_csv_path file exists and if the output_file file can be created.
 *
 * @param dist_csv_path Path to the dist_csv_path file.
 * @param output_file Path to the output_file file.
 * @throw `EXIT_FAILURE` if any of the input arguments is invalid.
 */
void validate_input(const char* dist_csv_path, const char* node_to_find, const char* output_file) {
    if (strcmp(dist_csv_path, output_file) == 0)
        raise_error("dist_csv_path and output_file cannot be the same");

    FILE* dist_csv_path_fp = fopen(dist_csv_path, "r");
    if (!dist_csv_path_fp)
        raise_error("dist_csv_path file does not exist -> %s", dist_csv_path);

    if (strlen(node_to_find) == 0) {
        fclose(dist_csv_path_fp);

        raise_error("node_to_find cannot be empty.\n");
    }

    FILE* output_file_fp = fopen(output_file, "w");
    if (!output_file_fp) {
        fclose(dist_csv_path_fp);

        raise_error("output_file file cannot be written -> %s\n", output_file);
    }

    fclose(dist_csv_path_fp);
    fclose(output_file_fp);
}

int main(int argc, const char* argv[]) {
    if (argc != 4)
        raise_error(
            "Usage:\n"
            "  %s <dist_csv_path> <node_to_find> <output_file>\n"
            "Options:\n"
            "  <dist_csv_path> Path to the csv file.\n"
            "  <node_to_find> Node (string) to find in the graph.\n"
            "  <output_file> Path where to print the output.\n"
            "Example:\n"
            "  %s data/italian_dist_graph.txt torino data/output.txt",
            argv[0],
            argv[0]
        );

    validate_input(argv[1], argv[2], argv[3]);
    
    return EXIT_SUCCESS;
}