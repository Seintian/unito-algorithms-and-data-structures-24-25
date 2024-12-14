/**
 * @file main.c
 * @brief Command Line Interface (CLI) application for traversing a graph and writing visited nodes to a file.
 *
 * @mainpage Graph Traversal CLI Application
 *
 * @section overview Overview
 * This project is a Command Line Interface (CLI) application designed to traverse a graph represented using hash tables. 
 * Starting from a specified node, the program visits all reachable nodes and writes them to an output file.
 *
 * @section usage Usage
 * The application is executed with the following command:
 * ```
 * ./bin/main_ex2(.exe) <dist_csv_path> <node_to_find> <output_file>
 * ```
 * - `<dist_csv_path>`: Path to the CSV file containing the graph representation.
 * - `<node_to_find>`: The starting node for the graph traversal.
 * - `<output_file>`: Path to the output file where the visited nodes will be written.
 *
 * Example:
 * ```
 * ./bin/main_ex2(.exe) data/italian_dist_graph.txt torino data/output.txt
 * ```
 *
 * @section file_structure File Structure
 *
 * - **main.c**: Contains the main entry point for the application. It handles command-line argument parsing, input validation, graph traversal, and writing results to the output file.
 * - **graph.h**: Declares functions for managing the graph, including adding nodes, edges, and traversing nodes.
 * - **hashtable.h**: Provides the implementation of a hash table used to store graph nodes and edges.
 * - **file_io.h**: Contains functions for reading graph data from a CSV file and writing visited nodes to an output file.
 *
 * @section modules Modules and Functions
 *
 * - **Input Validation**:
 *   - `validate_input`: Ensures the input CSV file exists and is readable, and checks the output file can be created.
 * - **Graph Operations**:
 *   - `load_graph`: Reads the graph from the CSV file and populates the hash table structure.
 *   - `traverse_graph`: Traverses the graph starting from the specified node.
 * - **File Operations**:
 *   - `read_csv`: Reads the graph structure from a CSV file.
 *   - `write_output`: Writes visited nodes to the specified output file.
 *
 * @section graph_structure Graph Structure
 *
 * The graph is represented using hash tables. Each node is stored as a key, with its neighbors stored as keys of other HashTables which have structs `Edge` as values.
 *
 * Example CSV format:
 * ```
 * torino,milano,140.325234
 * torino,genova,170.824345
 * milano,venezia,280.765567
 * ```
 *
 * @section traversal_logic Traversal Logic
 *
 * The graph traversal starts from the `node_to_find` provided as input. It visits all reachable nodes using a depth-first or breadth-first search algorithm.
 * Visited nodes are recorded in the order they are traversed and written to the output file.
 *
 * @section error_handling Error Handling
 *
 * The application validates:
 * - The input CSV file exists and can be read.
 * - The output file can be created.
 * - The starting node exists in the graph.
 *
 * If any validation fails, the application prints an error message and exits with `EXIT_FAILURE`.
 *
 * @section performance Performance
 *
 * The performance of the graph traversal depends on the number of nodes and edges in the graph:
 * - Time complexity: O(V + E), where V is the number of nodes and E is the number of edges.
 * - Space complexity: O(V + E) for storing the graph in hash tables.
 *
 * @section compilation Compilation Instructions
 * To compile the application, use:
 * ```
 * make all
 * ```
 * To compile and execute the tests, use:
 * ```
 * make test
 * ```
 */

#include "graph.h"
#include "hashtable.h"
#include "queue.h"
#include "io_lib.h"
#include "error_logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static int compare_string(const void* a, const void* b) {
    return strcmp((const char*) a, (const char*) b);
}

static unsigned long hash(const void* key) {
    unsigned long hash = 5381;
    const char* str = (const char*) key;

    while (*str) {
        hash = ((hash << 5) + hash) + *str++;
    }

    return hash;
}

static size_t count_lines(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp)
        return 0;

    size_t lines = 0;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp))
        lines++;

    fclose(fp);
    return lines;
}

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

    /**
     * TODO: directed -> 1 or 0?
     * Input:
     * monteriggioni,casa nagli,4582.425363560589
     * casa nagli,monteriggioni,4582.425363560589
     */
    Graph gr = graph_create(1, 1, compare_string, hash);
    if (!gr)
        raise_error("Error creating graph");

    size_t records = count_lines(argv[1]);
    if (records == 0)
        raise_error("Empty input file");

    FILE* dist_csv_path_fp = fopen(argv[1], "r");
    if (!dist_csv_path_fp)
        raise_error("Error opening input file");

    size_t records_read = read_records(dist_csv_path_fp, gr, records);
    if (records_read == 0)
        raise_error("Error reading records from file");

    void** visited_nodes = breadth_first_visit(gr, (void*) argv[2], compare_string, hash);
    if (!visited_nodes)
        raise_error("Error traversing graph");

    FILE* output_file = fopen(argv[3], "w");
    if (!output_file)
        raise_error("Error opening output file");

    size_t nodes_written = write_output(output_file, (const char**) visited_nodes);
    if (nodes_written == 0)
        raise_error("Error writing output");

    fclose(output_file);
    fclose(dist_csv_path_fp);

    graph_free(gr);
    free(visited_nodes);

    return EXIT_SUCCESS;
}