#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io_lib.h"
#include "graph.h"
#include "error_logger.h"


const char* recordReadFmt = "%252[^,],%252[^,],%lf\n";
const char* recordWriteFmt = "%s\n";

size_t read_records(FILE* infile, Graph nodes, size_t n_records) {
    size_t records_read = 0;
    char line[MAX_LINE_SIZE];
    char place1[MAX_STRING_LENGTH];
    char place2[MAX_STRING_LENGTH];
    double _distance;

    while (records_read < n_records && fgets(line, MAX_LINE_SIZE, infile)) {
        if (sscanf(line, recordReadFmt, place1, place2, &_distance) != 3)
            raise_error("Error reading record from file");

        double* distance = malloc(sizeof(double));
        if (!distance)
            raise_error("Memory allocation error while reading records");

        *distance = _distance;

        if (graph_add_node(nodes, strdup(place1)) == -1)
            raise_error("Error adding node \"%s\" to graph after %zu records", place1, records_read);

        if (graph_add_node(nodes, strdup(place2)) == -1)
            raise_error("Error adding node \"%s\" to graph after %zu records", place2, records_read);

        if (graph_add_edge(nodes, place1, place2, distance) != 1)
            raise_error("Error adding edge \"%s - %s\" to graph after %zu records", place1, place2, records_read);

        records_read++;
    }

    return records_read;
}

size_t write_output(FILE* outfile, const char** nodes) {
    size_t nodes_written = 0;

    for (size_t i = 0; nodes[i] != NULL; i++) {
        if (fprintf(outfile, recordWriteFmt, nodes[i]) > 0)
            nodes_written++;
    }

    return nodes_written;
}