/**
 * @file test_io_lib.c
 * @brief Unit tests for the I/O library functions.
 * 
 * This file contains the implementation of unit tests for the I/O library functions.
 */

#include "test_io_lib.h"
#include "unity.h"
#include "io_lib.h"
#include "graph.h"
#include <string.h>


/**
 * @brief Compares two strings for sorting.
 * 
 * This function is used to compare two strings in lexicographical order
 * for sorting purposes, typically used with qsort.
 * 
 * @param a Pointer to the first string.
 * @param b Pointer to the second string.
 * @return An integer less than, equal to, or greater than zero if
 *         the first string is found to be less than, equal to, or greater
 *         than the second string, respectively.
 */
static int compare_string(const void* a, const void* b) {
    return strcmp((const char*) a, (const char*) b);
}

/**
 * @brief Hash function for strings.
 * 
 * This function generates a hash value for a given string using the
 * DJB2 algorithm, commonly used for hash tables.
 * 
 * @param key Pointer to the string to be hashed.
 * @return The hash value of the string.
 */
static unsigned long hash(const void* key) {
    unsigned long hash = 5381;
    const char* str = (const char*) key;

    while (*str) {
        hash = ((hash << 5) + hash) + *str++;
    }

    return hash;
}

/**
 * @brief Test the reading of records from a file.
 * 
 * This function tests the ability to read records from a CSV file
 * and populate a graph structure with the data. It verifies the number
 * of records read, the number of nodes and edges in the graph, and
 * ensures that the file is read correctly.
 */
void test_read_records(void) {
    FILE* infile = fopen("test_input.csv", "w+");
    TEST_ASSERT_NOT_NULL(infile);  /**< Ensure the input file is opened successfully */
    fprintf(infile, "PlaceA,PlaceB,12.5\nPlaceC,PlaceD,7.8\n");  /**< Write sample data to the file */
    rewind(infile);  /**< Rewind the file pointer to the beginning */

    Graph graph = graph_create(1, 1, compare_string, hash);  /**< Create a new graph */
    size_t records_read = read_records(infile, graph, 2);  /**< Read records from the file */
    TEST_ASSERT_EQUAL(2, records_read);  /**< Ensure the correct number of records are read */

    // Verify graph contents
    TEST_ASSERT_EQUAL(4, graph_num_nodes(graph));  /**< Ensure the graph has the correct number of nodes */
    TEST_ASSERT_EQUAL(2, graph_num_edges(graph));  /**< Ensure the graph has the correct number of edges */

    graph_free(graph);  /**< Free the graph after the test */
    fclose(infile);  /**< Close the input file */
    remove("test_input.csv");  /**< Remove the test input file */
}

/**
 * @brief Test writing output to a file.
 * 
 * This function tests the ability to write output to a CSV file,
 * ensuring that nodes are written correctly. It then verifies the
 * contents of the output file to ensure the correct data was written.
 */
void test_write_output(void) {
    FILE* outfile = fopen("test_output.csv", "w");
    TEST_ASSERT_NOT_NULL(outfile);  /**< Ensure the output file is opened successfully */

    const char* nodes[] = {"Node1", "Node2", "Node3", NULL};  /**< Sample nodes to write */
    size_t nodes_written = write_output(outfile, nodes);  /**< Write nodes to the output file */
    TEST_ASSERT_EQUAL(3, nodes_written);  /**< Ensure the correct number of nodes are written */

    fclose(outfile);  /**< Close the output file */

    // Verify file contents
    FILE* infile = fopen("test_output.csv", "r");
    char buffer[MAX_LINE_SIZE];
    TEST_ASSERT_NOT_NULL(infile);  /**< Ensure the input file is opened successfully */
    TEST_ASSERT_NOT_NULL(fgets(buffer, MAX_LINE_SIZE, infile));  /**< Read the first line */
    TEST_ASSERT_EQUAL_STRING("Node1\n", buffer);  /**< Ensure the first node is written correctly */
    TEST_ASSERT_NOT_NULL(fgets(buffer, MAX_LINE_SIZE, infile));  /**< Read the second line */
    TEST_ASSERT_EQUAL_STRING("Node2\n", buffer);  /**< Ensure the second node is written correctly */
    TEST_ASSERT_NOT_NULL(fgets(buffer, MAX_LINE_SIZE, infile));  /**< Read the third line */
    TEST_ASSERT_EQUAL_STRING("Node3\n", buffer);  /**< Ensure the third node is written correctly */

    fclose(infile);  /**< Close the input file */
    remove("test_output.csv");  /**< Remove the test output file */
}
