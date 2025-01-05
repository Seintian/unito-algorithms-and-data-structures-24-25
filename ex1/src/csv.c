/**
 * @file csv_operations.c
 * @brief This file contains the implementation of CSV reading, writing, and comparison functions.
 *
 * This file provides functions to read and write CSV records into an array, compare records
 * based on different fields, count lines in a file, and handle whitespace trimming.
 */

#include "csv.h"
#include "error_logger.h"
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


const char* recordReadFmt = "%d,%239[^,],%d,%lf\n";
const char* recordWriteFmt = "%d,%s,%d,%lf\n";

int compare_field1(const void* a, const void* b) {
    const Record* recordA = (const Record*)a;
    const Record* recordB = (const Record*)b;
    
    return strcmp(recordA -> field1, recordB -> field1);
}

int compare_field2(const void* a, const void* b) {
    const Record* recordA = (const Record*)a;
    const Record* recordB = (const Record*)b;

    return recordA -> field2 - recordB -> field2;
}

int compare_field3(const void* a, const void* b) {
    const Record* recordA = (const Record*)a;
    const Record* recordB = (const Record*)b;

    double res = recordA -> field3 - recordB -> field3;

    if (res < 0)
        return -1;

    else if (res > 0)
        return 1;

    else
        return 0;
}

size_t count_lines(FILE* file) {
    size_t n_lines = 0;
    char buffer[MAX_LINE_SIZE];

    while (fgets(buffer, MAX_LINE_SIZE, file))
        n_lines++;

    rewind(file);

    return n_lines;
}

size_t read_records(FILE* infile, RecordPtr records, size_t n_records) {
    size_t read_count = 0;
    char* temp_buffer = malloc(MAX_FIELD1_SIZE);
    if (temp_buffer == NULL){
        print_error("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (; read_count < n_records; read_count++) {
        if (fscanf(
            infile, 
            recordReadFmt, 
            &records[read_count].id, 
            temp_buffer, 
            &records[read_count].field2, 
            &records[read_count].field3
        ) != N_FIELDS_IN_RECORD)
            break;

        records[read_count].field1 = malloc(strlen(temp_buffer) + 1);
        if (records[read_count].field1 == NULL){
            print_error("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        strcpy(records[read_count].field1, temp_buffer);
    }

    free(temp_buffer);

    return read_count;
}

size_t write_records(FILE* outfile, RecordPtr records, size_t n_records) {
    size_t n_wrote_records = 0;

    for (; n_wrote_records < n_records; n_wrote_records++)
        if (
            fprintf(
                outfile, 
                recordWriteFmt,
                records[n_wrote_records].id,
                records[n_wrote_records].field1,
                records[n_wrote_records].field2,
                records[n_wrote_records].field3
            ) == 0
        )
            break;

    return n_wrote_records;
}
