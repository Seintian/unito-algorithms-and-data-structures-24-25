/**
 * @file main.c
 * @brief Command Line Interface (CLI) application for sorting records from a CSV file.
 *
 * This file contains the implementation of a CLI application that reads records from a CSV file,
 * sorts them using either merge sort or quick sort based on a specified field, and writes the sorted
 * records to an output file. The main function serves as the entry point for the application,
 * parsing command line arguments and executing the appropriate functionality.
 *
 * Usage:
 *   ./application <input_file> <output_file> <algorithm>
 *
 * Options:
 *   <input_file>   Path to the input CSV file.
 *   <output_file>  Path to the output CSV file (must be different from input_file).
 *   <algorithm>    Sorting algorithm to use (0 for merge sort, 1 for quick sort).
 *
 * Example:
 *   ./application input.csv output.csv 0
 *
 * The main function handles the initialization and execution of the application
 * based on the provided command line arguments.
 */

#include "algo.h"
#include <stdio.h>
#include <time.h>
#include <string.h>


#define MAX_LINE_SIZE 128

/**
 * @brief Structure representing a record with four fields.
 * 
 * This structure represents a record with four fields: an integer ID, a string field1,
 * an integer field2, and a double field3. The structure is used to store the records
 * read from the input file.
 * 
 * This executable can only accept CSV files with the following format:
 * 
 *    ID,field1,field2,field3
 * 
 * where ID is an integer, field1 is a string with at most 99 characters, field2 is an integer,
 * and field3 is a double.
 */
typedef struct _Record {
    int id;
    char field1[100];
    int field2;
    double field3;

} Record, *RecordPtr;

/**
 * @brief Generic pointer to a comparison function for sorting records by different fields.
 *
 * This global pointer is used to store the address of a comparison function that is chosen in main
 *
 * @param a Pointer to the first record.
 * @param b Pointer to the second record.
 * @return A negative value if the first record is less than the second, zero if they are equal,
 *         and a positive value if the first record is greater than the second.
 */
int (*compare_records)(const void* a, const void* b);

/**
 * @brief Compares two records based on the field1 field.
 *
 * This function compares two records based on the field1 field. It is used as a comparison
 * function for the quick_sort and merge_sort functions.
 * 
 * This definition is common to all the compare_fieldX functions.
 *
 * @param a Pointer to the first record.
 * @param b Pointer to the second record.
 * @return A negative value if the first record is less than the second, zero if they are equal,
 *         and a positive value if the first record is greater than the second.
 */
int compare_field1(const void* a, const void* b) {
    return strcmp(((RecordPtr) a) -> field1, ((RecordPtr) b) -> field1);
}

int compare_field2(const void* a, const void* b) {
    return ((RecordPtr) a) -> field2 - ((RecordPtr) b) -> field2;
}

int compare_field3(const void* a, const void* b) {
    double res = (((RecordPtr) a) -> field3 - ((RecordPtr) b) -> field3);

    if (res < 0)
        return -1;

    else if (res > 0)
        return 1;

    else
        return 0;
}

/**
 * @brief Validates the input arguments.
 *
 * This function validates the input arguments of the program.
 * It checks if the input file exists, if the output file can be created,
 * and if the algorithm is valid.
 *
 * @param input_file Path to the input file.
 * @param output_file Path to the output file.
 * @param algorithm Algorithm to be used (0 for merge sort, 1 for quick sort).
 * @return 0 if the input arguments are valid, 1 if the input file does not exist,
 *         2 if the output file cannot be created, 3 if the algorithm is invalid.
 */
void validate_input(char* input_file, char* output_file, char* algorithm) {
    if (strcmp(input_file, output_file) == 0) {
        printf("Error: input_file and output_file cannot be the same " \
               "-> input_file: %s, output_file: %s\n", input_file, output_file);
        exit(EXIT_FAILURE);
    }

    FILE* input = fopen(input_file, "r");
    if (input == NULL) {
        printf("Error: input file does not exist -> %s\n", input_file);
        exit(EXIT_FAILURE);
    }

    FILE* output = fopen(output_file, "w");
    if (output == NULL) {
        fclose(input);

        printf("Error: output file cannot be created " \
                "-> input_file: %s, output_file: %s\n", input_file, output_file);
        exit(EXIT_FAILURE);
    }

    int algo = atoi(algorithm);
    if (algo != 0 && algo != 1) {
        fclose(input);
        fclose(output);

        printf("Error: invalid algorithm (expected 0 or 1) -> %s\n", algorithm);
    }

    fclose(input);
    fclose(output);
}

/**
 * @brief Counts the number of lines in a file.
 *
 * @param file Pointer to the file.
 * @return Number of lines in the file.
 */
size_t count_lines(FILE* file) {
    size_t n_lines = 0;
    char buffer[MAX_LINE_SIZE];
    while (fgets(buffer, MAX_LINE_SIZE, file))
        n_lines++;

    rewind(file);

    return n_lines;
}

/**
 * @brief Reads records from a file and stores them in an array of RecordPtr.
 *
 * This function reads a specified number of records from the given input file
 * and stores them in the provided array of RecordPtr. The function assumes that
 * the file is already opened for reading and that the array has enough space to
 * hold the specified number of records.
 *
 * @param infile A pointer to the input file from which records are to be read.
 * @param records A pointer to an array of RecordPtr where the read records will be stored.
 * @param n_records The number of records to read from the file.
 */
void read_records(FILE* infile, RecordPtr records, size_t n_records) {
    for (size_t i = 0; i < n_records; i++) {
        size_t fields_read = fscanf(
            infile, 
            "%d,%99[^,],%d,%lf\n", 
            &(records[i].id), 
            records[i].field1, 
            &(records[i].field2), 
            &(records[i].field3)
        );

        if (fields_read != 4) {
            perror("Error reading record from CSV file");

            exit(EXIT_FAILURE);
        }
    }
}

/**
 * @brief Writes sorted records to a file.
 *
 * This function writes the sorted records to the output file in CSV format.
 *
 * @param outfile Pointer to the output file.
 * @param records Pointer to the array of sorted records.
 * @param n_records Number of records to write.
 */
void write_sorted_records(FILE* outfile, RecordPtr records, size_t n_records) {
    for (size_t i = 0; i < n_records; i++) {
        fprintf(
            outfile, 
            "%d,%s,%d,%lf\n", 
            records[i].id, 
            records[i].field1, 
            records[i].field2, 
            records[i].field3
        );
    }
}

/**
 * @brief Sorts the records in the input file and writes them to the output file.
 *
 * This function reads the records from the input file, sorts them using the specified
 * algorithm, and writes the sorted records to the output file.
 *
 * @param infile Pointer to the input file.
 * @param outfile Pointer to the output file.
 * @param field Field to be used as the key for sorting.
 * @param algo Algorithm to be used (0 for merge sort, 1 for quick sort).
 */
void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo) {
    // DEBUG:
    clock_t start = clock(), end;
    double total_time;

    size_t n_records = count_lines(infile);

    RecordPtr records = (RecordPtr) malloc(n_records * sizeof(Record));
    if (!records) {
        perror("Error allocating memory for records in CSV file");

        return;
    }

    read_records(infile, records, n_records);

    // DEBUG:
    end = clock();
    total_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Reading records: %f seconds\n", total_time);

    // DEBUG:
    start = clock();

    switch (algo) {
        case 0:
            merge_sort(records, n_records, sizeof(Record), compare_records);
            break;

        case 1:
            quick_sort(records, n_records, sizeof(Record), compare_records);
            break;

        default:
            break;
    }
    
    // DEBUG:
    end = clock();
    total_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Sorting with %s_sort: %f seconds\n", algo ? "quick" : "merge", total_time);

    start = clock();
    write_sorted_records(outfile, records, n_records);

    // DEBUG:
    end = clock();
    total_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Writing records: %f seconds\n", total_time);
}

/**
 * @brief Main function.
 *
 * This function is the entry point of the program. It validates the input arguments,
 * reads the records from the input file, sorts them using the specified algorithm, and
 * writes the sorted records to the output file.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return `EXIT_SUCCESS` if the program executed successfully,
 *         `EXIT_FAILURE` if the input arguments are invalid.
 */
int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage:\n");
        printf("  %s <input_file> <output_file> <algorithm>\n\n", argv[0]);
        printf("Options:\n");
        printf("  <input_file>   path to the input file\n");
        printf("  <output_file>  path to the output file (different from input_file)\n");
        printf("  <algorithm>    0 for merge sort, 1 for quick sort\n\n");
        printf("Example:\n");
        printf("  %s input.csv output.csv 0\n", argv[0]);

        return EXIT_FAILURE;
    }

    validate_input(argv[1], argv[2], argv[3]);

    for (size_t i = 0; i < 3; i++) {
        FILE* infile = fopen(argv[1], "r");
        FILE* outfile = fopen(argv[2], "w");
        size_t algo = atoi(argv[3]);
        clock_t start, end;
        double total_time;

        switch (i) {
            case 0:
                compare_records = compare_field1;
                break;

            case 1:
                compare_records = compare_field2;
                break;

            case 2:
                compare_records = compare_field3;
                break;

            default:
                break;
        }

        printf("\nSorting by field%zu...\n", i + 1);

        start = clock();
        sort_records(infile, outfile, i, algo);
        end = clock();

        total_time = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Total time elapsed: %f seconds\n", total_time);

        fclose(infile);
        fclose(outfile);

        if (i < 2) {
            printf("\nPress Enter to continue... ");
            getchar();
        }
    }

    return EXIT_SUCCESS;
}