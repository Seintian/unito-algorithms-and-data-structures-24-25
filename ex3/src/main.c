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
 * The implementation also includes unit tests using the Unity framework to verify the functionality of various operations.
 * 
 * @section features_sec Features
 * - **Custom Hash Function Support**: The hash table allows the user to specify custom hash functions suitable for the key type.
 * - **Dynamic Resizing**: Automatic resizing based on configurable load factors to optimize performance.
 * - **Collision Resolution**: Implemented using linked lists for collision management.
 * - **Various Utility Functions**: Functions to retrieve keys, values, and check for key existence.
 * - **Load Factor Management**: Handles upscaling and downscaling of capacity based on current usage.
 * 
 * @section usage_sec Usage
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
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"


int main(int argc, char* argv[]) {
    printf("Hello, World!\n");

    return EXIT_SUCCESS;
}