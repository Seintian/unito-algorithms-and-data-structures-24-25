/**
 * @file main.c
 * @brief Entry point for the Ex3 project.
 * 
 * @mainpage Hash Table Implementation Documentation
 * 
 * @section intro_sec Introduction
 * This project provides an implementation of a generic hash table data structure in C, with the following features:
 * - Efficient key-value storage and retrieval using custom hash and comparison functions.
 * - Support for dynamic resizing to maintain optimal load factors.
 * - Collision handling through linked lists (chaining).
 * 
 * @section usage_sec Usage
 * The application is executed with the following command:
 * ```
 * ./bin/main_ex3(.exe) <input_file> <min_length>
 * ```
 * - `<input_file>`: Path to the text file containing words to be processed.
 * - `<min_length>`: Minimum length of words to consider for frequency calculation.
 * 
 * Example:
 * ```
 * ./bin/main_ex3(.exe) data/iliade.txt 6
 * ```
 * 
 * The implementation also includes unit tests using the Unity framework to verify the functionality of various operations.
 * 
 * @section features_sec Features
 * - **Custom Hash Function Support**: The hash table allows the user to specify custom hash functions suitable for the key type.
 * - **Dynamic Resizing**: Automatic resizing based on configurable load factors to optimize performance.
 * - **Collision Resolution**: Implemented using linked lists for collision management.
 * - **Various Utility Functions**: Functions to retrieve keys, values, and check for key existence.
 * - **Load Factor Management**: Handles upscaling and downscaling of capacity based on current usage.
 * 
 * @section data_structures_sec Data Structures
 * The main data structures in this project are:
 * - `HashNode`: Represents an entry in the hash table.
 * - `HashTable`: The hash table structure containing buckets, capacity, and utility function pointers.
 * 
 * **Basic API Functions**:
 * - `HashTable* hash_table_create(int (*compare)(const void*, const void*), unsigned long (*hash_func)(const void*))`
 * - `void hash_table_put(HashTable* table, const void* key, const void* value)`
 * - `void* hash_table_get(const HashTable* table, const void* key)`
 * - `void hash_table_remove(HashTable* table, const void* key)`
 * - `void hash_table_clear(HashTable* table)`
 * - `void hash_table_free(HashTable* table)`
 * 
 * **Advanced Operations**:
 * - `hash_table_map()` for applying a function to all entries.
 * - `hash_table_equals()` for comparing two hash tables.
 * - `hash_table_keyset()` and `hash_table_values()` for retrieving keys and values.
 * 
 * @section testing_sec Unit Testing
 * Unit tests are implemented using the Unity framework and can be found in the `test` directory. They cover:
 * - Creation and basic insertion operations.
 * - Key updates and retrievals.
 * - Resizing behavior.
 * - Clearing and memory management.
 * 
 * **Example Test Functions**:
 * - `test_hash_table_create()`
 * - `test_hash_table_put_and_get()`
 * - `test_hash_table_remove()`
 * - `test_hash_table_map()`
 * 
 * @section dependencies_sec Dependencies
 * - Standard C libraries: `<stdlib.h>`, `<string.h>`, `<stdio.h>`.
 * - **Unity Framework**: For unit testing.
 * 
 * @section compile_sec Compilation
 * Compile the project with:
 * ```
 * make all
 * ```
 * To compile and execute the tests, use:
 * ```
 * make test
 * ```
 * 
 * @see test_main.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"
#include "text_io.h"
#include "error_logger.h"


void find_max_word(const HashTable* table, int min_length) {
    void** keys = hash_table_keyset(table);
    if (!keys) {
        print_error("failed to get keys from hash table");
        exit(EXIT_FAILURE);
    }

    void** values = hash_table_values(table);
    if (!values) {
        free(keys);

        print_error("failed to get values from hash table");
        exit(EXIT_FAILURE);
    }

    char* max_word = NULL;
    int max_freq = 0;

    for (size_t i = 0; i < hash_table_size(table); i++) {
        char* word = (char*) keys[i];
        int freq = *(int*) values[i];

        if (strlen(word) >= min_length && freq > max_freq) {
            max_word = word;
            max_freq = freq;
        }
    }

    if (max_word)
        printf("Most frequent word with at least %d characters: %s (%d occurrences)\n", min_length, max_word, max_freq);

    else
        printf("No words with at least %d characters found\n", min_length);

    free(keys);
    free(values);
}

void free_key_value(const void* key, const void* value) {
    free((void*) key);
    free((void*) value);
}

/**
 * @brief Clears the hash table and frees the memory.
 *
 * This function clears the hash table and frees the memory allocated for the keys and values.
 *
 * @param table Pointer to the hash table to clear.
 */
void clear_words_hash_table(HashTable* table) {
    if (table == NULL) {
        print_error("Error: hash table is NULL");
        exit(EXIT_FAILURE);
    }

    hash_table_map(table, free_key_value);
    hash_table_free(table);
}

/**
 * @brief Hash function for strings.
 *
 * This function generates a hash value for a given string.
 * It uses the djb2 algorithm to calculate the hash value.
 *
 * @param key The string to hash.
 * @return The hash value of the string.
 */
unsigned long hash_string(const void* key) {
    const char* str = (const char*) key;
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

/**
 * @brief Comparison function for strings.
 *
 * This function compares two strings and returns the result.
 *
 * @param a The first string to compare.
 * @param b The second string to compare.
 * @return 0 if the strings are equal, non-zero otherwise.
 */
int compare_string(const void* a, const void* b) {
    return strcmp((const char*) a, (const char*) b);
}

/**
 * @brief Validates the input arguments.
 *
 * This function validates the input arguments of the program.
 * It checks if the text file path is valid and if the minimum word length is a positive integer.
 *
 * @param text_path Path to the text file.
 * @param min_word_length Minimum length of words.
 * @throw `EXIT_FAILURE` if any of the input arguments is invalid.
 */
void validate_input(const char* text_path, const char* min_word_length) {
    FILE* text_fp = fopen(text_path, "r");
    if (!text_fp) {
        print_error("dictionary file does not exist -> %s", text_path);
        exit(EXIT_FAILURE);
    }

    int min_length = atoi(min_word_length);
    if (min_length < 0) {
        print_error("Error: minimum word length must be a positive integer -> %s", min_word_length);
        exit(EXIT_FAILURE);
    }

    fclose(text_fp);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        print_error(
            "Usage:\n"
            "  %s <text_path> <min_word_length>\n"
            "Options:\n"
            "  <text_path> Path to the text file.\n"
            "  <min_word_length> Minimum length of words.\n"
            "Example:\n"
            "  %s data/iliade.txt 6\n",
            argv[0],
            argv[0]
        );
        exit(EXIT_FAILURE);
    }

    validate_input(argv[1], argv[2]);

    HashTable* table = hash_table_create(&compare_string, &hash_string);
    if (!table) {
        print_error("Error: failed to create hash table");
        exit(EXIT_FAILURE);
    }

    FILE* text_fp = fopen(argv[1], "r");
    if (!text_fp) {
        free(table);

        print_error("Error: failed to open text file");
        exit(EXIT_FAILURE);
    }

    printf("Reading text file...\n");
    if (read_text(text_fp, &table) == -1) {
        fclose(text_fp);
        clear_words_hash_table(table);

        print_error("failed to read text file");
        exit(EXIT_FAILURE);
    }

    printf("Finding most frequent word with at least %d characters...\n", atoi(argv[2]));
    find_max_word((const HashTable*) table, atoi(argv[2]));

    printf("Freeing memory...\n");
    fclose(text_fp);
    clear_words_hash_table(table);

    return EXIT_SUCCESS;
}