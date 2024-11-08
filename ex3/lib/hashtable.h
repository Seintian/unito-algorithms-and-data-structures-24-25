#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_


typedef struct HashNode HashNode;
typedef struct HashTable HashTable;

// Function to create a new hash table
HashTable* hash_table_create(int (*compare)(const void*, const void*), unsigned long (*hash_func)(const void*));

// Basic hash table operations
void hash_table_put(HashTable* table, const void* key, const void* value);                     // Insert or update a key-value pair
void* hash_table_get(const HashTable* table, const void* key);                                 // Retrieve a value by key
int hash_table_contains_key(const HashTable* table, const void* key);                          // Check if a key exists
void hash_table_remove(HashTable* table, const void* key);                                     // Remove a key-value pair
int hash_table_size(const HashTable* table);                                                   // Get the current size of the hash table
int hash_table_capacity(const HashTable* table);                                               // Get the current capacity of the hash table
void** hash_table_keyset(const HashTable* table);                                              // Get an array of all keys
void hash_table_free(HashTable* table);                                                        // Free the entire hash table

// Extended hash table operations
float hash_table_load_factor(const HashTable* table);                                          // Calculate the current load factor
void hash_table_replace(const HashTable* table, const void* key, const void* new_value);       // Replace the value for an existing key
void hash_table_clear(HashTable* table);                                                       // Clear all elements from the hash table
void hash_table_map(const HashTable* table, void (*func)(const void* key, const void* value)); // Apply a function to each key-value pair
void** hash_table_values(const HashTable* table);                                              // Get an array of all values
int hash_table_equals(const HashTable* table1, const HashTable* table2);                       // Check if two hash tables are equal
HashTable* hash_table_copy(const HashTable* table);                                            // Create a deep copy of the hash table
void hash_table_merge(HashTable* dest, const HashTable* source);                               // Merge two hash tables

#endif // _HASHTABLE_H_