#include "graph.h"
#include "io_lib.h"
#include "error_logger.h"
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