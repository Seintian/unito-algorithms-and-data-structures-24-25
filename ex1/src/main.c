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
#include "csv.h"
#include <stdio.h>
#include <time.h>
#include <string.h>


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
 * @brief Validates the input arguments.
 *
 * This function validates the input arguments of the program.
 * It checks if the input file exists, if the output file can be created,
 * and if the algorithm is valid.
 *
 * @param input_file Path to the input file.
 * @param output_file Path to the output file.
 * @param algorithm Algorithm to be used (0 for merge sort, 1 for quick sort).
 * @throw `EXIT_FAILURE` if any of the input arguments is invalid.
 */
void validate_input(char* input_file, char* output_file, char* algorithm) {
    if (strcmp(input_file, output_file) == 0) {
        printf("Error: input_file and output_file cannot be the same " \
               "-> input_file: %s, output_file: %s\n", input_file, output_file);
        exit(EXIT_FAILURE);
    }

    FILE* input = fopen(input_file, "r");
    if (!input) {
        printf("Error: input file does not exist -> %s\n", input_file);
        exit(EXIT_FAILURE);
    }

    FILE* output = fopen(output_file, "w");
    if (!output) {
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
        exit(EXIT_FAILURE);
    }

    fclose(input);
    fclose(output);
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
 * @throw `EXIT_FAILURE` if an error occurs during memory allocation.
 */
void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo) {
    size_t n_records = count_lines(infile);
    time_t start, end;

    RecordPtr records = (RecordPtr) malloc(n_records * sizeof(Record));
    if (!records) {
        fprintf(stderr, "Error allocating memory for records in CSV file\n");
        exit(EXIT_FAILURE);
    }

    printf("Reading %zu records...\n", n_records);

    start = time(NULL);
    size_t n_read_records = read_records(infile, records, n_records);
    end = time(NULL);

    printf("Read %zu records in %lld seconds.\n", n_read_records, end - start);

    printf("Sorting records with %s_sort...\n", algo ? "quick" : "merge");

    start = time(NULL);
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
    end = time(NULL);

    printf("Sorted records in %lld seconds.\n", end - start);

    printf("Writing %zu sorted records...\n", n_records);

    start = time(NULL);
    size_t n_wrote_records = write_records(outfile, records, n_records);
    end = time(NULL);

    printf("Wrote %zu records in %lld seconds.\n", n_wrote_records, end - start);

    free(records);
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

        time_t start = time(NULL);
        sort_records(infile, outfile, i, algo);
        time_t end = time(NULL);

        printf("Total time in %lld seconds.\n", end - start);

        fclose(infile);
        fclose(outfile);

        fflush(outfile);

        if (i < 2) {
            printf("\nPress Enter to continue... ");
            getchar();

            exit(EXIT_SUCCESS);
        }
    }

    return EXIT_SUCCESS;
}