#include "graph.h"
#include "io_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void** breadth_first_visit(Graph gr, void* start, int (*compare)(const void*, const void*), unsigned long (*hash)(const void*));
// start è il nodo di partenza da cui cominciare la visita, la funzione restituisce l'array dei nodi nell'ordine di visita.
// eventualmente, la funzione restituisce null se il nodo start non è presente nel grafo gr.

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
    if (strcmp(dist_csv_path, output_file) == 0) {
        fprintf(stderr, "Error: dist_csv_path and output_file cannot be the same " \
               "-> dist_csv_path: %s, output_file: %s\n", dist_csv_path, output_file);
        exit(EXIT_FAILURE);
    }

    FILE* dist_csv_path_fp = fopen(dist_csv_path, "r");
    if (!dist_csv_path_fp) {
        fprintf(stderr, "Error: dist_csv_path file does not exist -> %s\n", dist_csv_path);
        exit(EXIT_FAILURE);
    }

    if (strlen(node_to_find) == 0) {
        fclose(dist_csv_path_fp);

        fprintf(stderr, "Error: node_to_find cannot be empty.\n");
        exit(EXIT_FAILURE);
    }

    FILE* output_file_fp = fopen(output_file, "w");
    if (!output_file_fp) {
        fclose(dist_csv_path_fp);

        fprintf(stderr, "Error: output_file file cannot be written -> %s\n", output_file);
        exit(EXIT_FAILURE);
    }

    fclose(dist_csv_path_fp);
    fclose(output_file_fp);
}

int main(int argc, const char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage:\n");
        fprintf(stderr, "  %s <dist_csv_path> <node_to_find> <output_file>\n", argv[0]);
        fprintf(stderr, "Options:\n");
        fprintf(stderr, "  <dist_csv_path> Path to the csv file.\n");
        fprintf(stderr, "  <node_to_find> Node (string) to find in the graph.\n");
        fprintf(stderr, "  <output_file> Path where to print the output.\n");
        fprintf(stderr, "Example:\n");
        fprintf(stderr, "  %s data/italian_dist_graph.txt torino data/output.txt\n", argv[0]);

        return EXIT_FAILURE;
    }

    validate_input(argv[1], argv[2], argv[3]);
    
    return EXIT_SUCCESS;
}