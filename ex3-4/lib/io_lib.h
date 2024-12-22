/**
 * @file io_lib.h
 * @brief Interface for reading and writing records from CSV files.
 */

#ifndef _IO_LIB_H
#define _IO_LIB_H

#include <stdlib.h>
#include <stdio.h>
#include "graph.h"


#define MAX_LINE_SIZE 512
#define MAX_STRING_LENGTH 252

/**
 * @brief A structure representing a record in the CSV file.
 * 
 * This structure contains the fields `place1`, `place2`, and `distance` which
 * represent the two places connected by an edge and the distance between them.
 */
typedef struct _Record {
    char* place1;
    char* place2;
    double distance;

} Record;

/**
 * @brief Format string for reading a record from a CSV file.
 * 
 * This format string is used in `fscanf` for reading each record with the fields: 
 * node1 (string), node2 (string), distance (double).
 */
extern const char* recordReadFmt;

/**
 * @brief Format string for writing a record to a CSV file.
 * 
 * This format string is used in `fprintf` for writing a record with the fields: 
 * node (string).
 */
extern const char* recordWriteFmt;

/**
 * @brief Reads records from a file and stores them in a graph of type `Graph`.
 *
 * This function reads a specified number of records from the given input file
 * and stores them in the provided Graph. The function assumes that
 * the file is already opened for reading and that the array has enough space to
 * hold the specified number of records.
 *
 * Assumptions:
 * 
 * - The CSV file must contain only valid records.
 * 
 * - The CSV file must have a trailing newline at the end.
 *
 * @param infile A pointer to the input file from which records are to be read.
 * @param nodes A pointer to a Graph where the read records will be stored.
 * @param n_records The number of records to read from the file.
 * @return The number of records successfully read from the file.
 */
size_t read_records(FILE* infile, Graph nodes, size_t n_records);

/**
 * @brief Writes records to a file.
 *
 * This function writes the specified number of nodes (strings) to the given output file.
 * The function assumes that the file is already opened for writing and that the
 * nodes array is NULL terminated.
 *
 * @param outfile A pointer to the output file to which nodes are to be written.
 * @param nodes A `NULL` terminated array of char* (strings) containing the nodes to be written.
 * @return The number of nodes successfully written to the file.
 */
size_t write_output(FILE* outfile, const char** nodes);

#endif // _IO_LIB_H