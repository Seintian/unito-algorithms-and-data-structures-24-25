/**
 * @file main.c
 * @brief Command Line Interface (CLI) application for sorting records from a CSV file.
 *
 * @mainpage CSV Sorting CLI Application
 *
 * @section overview Overview
 * This project is a Command Line Interface (CLI) application designed for sorting records from a CSV file. The user can choose between two sorting algorithms (merge sort and quick sort) and specify which field to sort by. The sorted records are then written to an output file.
 *
 * @section usage Usage
 * The application is executed with the following command:
 * ```
 * ./bin/main_ex1(.exe) <input_file> <output_file> <algorithm> <field>
 * ```
 * - `<input_file>`: Path to the input CSV file.
 * - `<output_file>`: Path to the output CSV file (must be different from `<input_file>`).
 * - `<algorithm>`: Sorting algorithm to use (0 for merge sort, 1 for quick sort).
 * - `<field>`: Field to be used as the key for sorting (0 for `field1`, 1 for `field2`, 2 for `field3`).
 *
 * Example:
 * ```
 * ./bin/main_ex1(.exe) input.csv output.csv 0 1
 * ```
 *
 * @section file_structure File Structure
 *
 * - **main.c**: Contains the main entry point for the application. It handles command line argument parsing, input validation, sorting, and writing results to the output file.
 * - **algo.h**: Declares the `merge_sort` and `quick_sort` functions used for sorting arrays.
 * - **csv.h**: Provides the interface for functions related to reading and writing CSV records and defines the `Record` structure.
 *
 * @section modules Modules and Functions
 *
 * - **Input Validation**: Ensures input and output files are valid and checks the sorting algorithm and field parameters.
 * - **Sorting Algorithms**:
 *   - `merge_sort`: A stable sorting algorithm implemented in `algo.h`.
 *   - `quick_sort`: A fast, in-place sorting algorithm implemented in `algo.h`.
 * - **CSV Operations**:
 *   - `read_records`: Reads CSV records from an input file.
 *   - `write_records`: Writes records to an output file in CSV format.
 *   - `count_lines`: Counts the number of records (lines) in a CSV file.
 *
 * @section record_structure Record Structure
 *
 * The `Record` structure represents a record with the following fields:
 * - `id` (integer)
 * - `field1` (string)
 * - `field2` (integer)
 * - `field3` (double)
 *
 * Example CSV format:
 * ```
 * 0,Hello,42,3.14
 * 1,Example,100,2.71
 * 2,Sample,200,1.23
 * ```
 *
 * @section sorting_details Sorting Logic
 *
 * The `compare_records` function pointer is set to one of the field comparison functions (`compare_field1`, `compare_field2`, or `compare_field3`), depending on the `field` argument provided by the user.
 *
 * @section error_handling Error Handling
 *
 * The application validates:
 * - The input and output files are different.
 * - The input file exists and can be read.
 * - The output file can be created.
 * - The specified algorithm and field parameters are valid.
 *
 * If any validation fails, the application prints an error message and exits with `EXIT_FAILURE`.
 *
 * @section performance Performance
 * The `merge_sort` algorithm is stable and has a time complexity of O(n log n). The `quick_sort` algorithm, although faster on average with a time complexity of O(n log n), may degrade to O(n^2) in the worst case.
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

#include "error_logger.h"
#include "algo.h"
#include "csv.h"
#include <time.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>


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
 * @param algorithm Algorithm to be used (1 for merge sort, 2 for quick sort).
 * @param field Field to be used as the key for sorting (1 for field1, 2 for field2, 3 for field3).
 * @throw `EXIT_FAILURE` if any of the input arguments is invalid.
 */
void validate_input(char* input_file, char* output_file, char* field, char* algorithm) {
    if (strcmp(input_file, output_file) == 0)
        raise_error(
            "input_file and output_file cannot be the same "
            "-> input_file: %s, output_file: %s",
            input_file,
            output_file
        );

    FILE* input = fopen(input_file, "r");
    if (!input)
        raise_error(
            "input file does not exist -> %s",
            input_file
        );

    FILE* output = fopen(output_file, "w");
    if (!output) {
        fclose(input);

        raise_error(
            "output file cannot be created "
            "-> input_file: %s, output_file: %s", input_file, output_file
        );
    }

    int fld = atoi(field);
    if (fld < 1 || fld > 3) {
        fclose(input);
        fclose(output);

        raise_error(
            "invalid field (expected 1, 2, or 3) -> %s",
            field
        );
    }

    int algo = atoi(algorithm);
    if (algo != 1 && algo != 2) {
        fclose(input);
        fclose(output);

        raise_error(
            "invalid algorithm (expected 1 or 2) -> %s",
            algorithm
        );
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
 * @param field Field to be used as the key for sorting (1 for field1, 2 for field2, 3 for field3).
 * @param algo Algorithm to be used (1 for merge sort, 2 for quick sort).
 * @throw `EXIT_FAILURE` if an error occurs during memory allocation.
 */
void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo) {
    switch (field) {
        case 1:
            compare_records = compare_field1;
            break;

        case 2:
            compare_records = compare_field2;
            break;

        case 3:
            compare_records = compare_field3;
            break;

        default:
            break;
    }

    printf("\nSorting by field%zu...\n", field);

    size_t n_records = count_lines(infile);
    time_t start;
    time_t end;

    RecordPtr records = (RecordPtr) malloc(n_records * sizeof(Record));
    if (!records)
        raise_error("Memory allocation failed");

    printf("Reading %zu records...\n", n_records);

    start = time(NULL);
    size_t n_read_records = read_records(infile, records, n_records);
    end = time(NULL);

    printf("Read %zu records in %" PRId64 " seconds.\n", n_read_records, end - start);

    printf("Sorting records with %s_sort...\n", algo == 2 ? "quick" : "merge");

    start = time(NULL);
    switch (algo) {
        case 1:
            merge_sort(records, n_read_records, sizeof(Record), compare_records);
            break;

        case 2:
            quick_sort(records, n_read_records, sizeof(Record), compare_records);
            break;

        default:
            break;
    }
    end = time(NULL);

    printf("Sorted records in %" PRId64 " seconds.\n", end - start);

    printf("Writing %zu sorted records...\n", n_read_records);

    start = time(NULL);
    size_t n_wrote_records = write_records(outfile, records, n_read_records);
    end = time(NULL);

    printf("Wrote %zu records in %" PRId64 " seconds.\n", n_wrote_records, end - start);

    for (size_t i = 0; i < n_read_records; i++)
        free(records[i].field1);

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
    if (argc != 5) {
        fprintf(stderr, "Usage:\n");
        fprintf(stderr, "  %s <input_file> <output_file> <field> <algorithm>\n\n", argv[0]);
        fprintf(stderr, "Options:\n");
        fprintf(stderr, "  <input_file>   path to the input file\n");
        fprintf(stderr, "  <output_file>  path to the output file (different from input_file)\n");
        fprintf(stderr, "  <field>        1 for field1, 2 for field2, 3 for field3\n\n");
        fprintf(stderr, "  <algorithm>    1 for merge sort, 2 for quick sort\n");
        fprintf(stderr, "Example:\n");
        fprintf(stderr, "  %s input.csv output.csv 1 2\n", argv[0]);

        return EXIT_FAILURE;
    }

    validate_input(argv[1], argv[2], argv[3], argv[4]);

    FILE* infile = fopen(argv[1], "r");
    FILE* outfile = fopen(argv[2], "w");
    size_t field = atoi(argv[3]);
    size_t algo = atoi(argv[4]);

    time_t start = time(NULL);
    sort_records(infile, outfile, field, algo);
    time_t end = time(NULL);

    printf("Total time in %" PRId64 " seconds.\n", end - start);

    if (infile)
        fclose(infile);

    fflush(outfile);

    if (outfile)
        fclose(outfile);

    return EXIT_SUCCESS;
}