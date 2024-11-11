/**
 * @file hashtable.h
 * @brief Implementation of a generic hash table data structure. Contains only functions declarations and opaque structure definitions.
 */

#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

/**
 * @brief Enum to define return status codes.
 * 
 * RETURN_FAILURE: Indicates a failure with a value of -1.
 * RETURN_SUCCESS: Indicates success with a value of 0.
 */
typedef enum _ReturnType {
    RETURN_FAILURE = -1,
    RETURN_SUCCESS = 0

} ReturnType;

typedef struct HashNode HashNode;
typedef struct HashTable HashTable;

/**
 * @brief creates a new HashTable
 * 
 * Initializes a new hash table with the given comparison and hash functions.
 * 
 * @param compare The comparison function for keys: should return 0 if keys are equal, non-zero otherwise
 * @param hash_func The hash function for keys: should return a unique hash (unsigned long) for each key
 * @return HashTable* to the newly created hash table on success, or NULL on failure
 */
HashTable* hash_table_create(int (*compare)(const void*, const void*), unsigned long (*hash_func)(const void*));

// Basic hash table operations

/**
 * @brief puts a key-value pair into the hash table
 * 
 * Inserts a key-value pair into the hash table. If the key already exists, the value is updated.
 * If the load factor exceeds the threshold, the table is resized.
 * 
 * ```
 * table -> capacity = next_prime(table -> capacity * 2)
 * ```
 * 
 * @param table The hash table to insert into
 * @param key The key to insert
 * @param value The value to insert
 */
void hash_table_put(HashTable* table, const void* key, const void* value);

/**
 * @brief gets the value for a given key
 * 
 * Retrieves the value for a given key from the hash table. If the key does not exist, returns NULL.
 * 
 * @param table The hash table to retrieve from
 * @param key The key to retrieve
 * @return void* corresponding to the value for the given key, NULL if the key does not exist or the table is NULL
 */
void* hash_table_get(const HashTable* table, const void* key);

/**
 * @brief checks if a key exists in the hash table
 * 
 * Checks if a key exists in the hash table. Returns 1 if the key exists, 0 otherwise.
 * 
 * @param table The hash table to check
 * @param key The key to check for
 * @return integer 1 if the key exists, 0 if it does not, or RETURN_FAILURE on failure
 */
int hash_table_contains_key(const HashTable* table, const void* key);

/**
 * @brief removes a key-value pair from the hash table
 * 
 * Removes a key-value pair from the hash table. If the load factor falls below the threshold, the table is resized.
 * 
 * ```
 * table -> capacity = next_prime(table -> capacity / 2)
 * ```
 * 
 * @param table The hash table to remove from
 * @param key The key to remove
 */
void hash_table_remove(HashTable* table, const void* key);

/**
 * @brief gets the current size of the hash table
 * 
 * Returns the current number of key-value pairs in the hash table.
 * 
 * @param table The hash table to get the size of
 * @return integer representing the size of the hash table, or RETURN_FAILURE on failure
 */
int hash_table_size(const HashTable* table);

/**
 * @brief gets the current capacity of the hash table
 * 
 * Returns the current capacity of the hash table (number of buckets).
 * 
 * @param table The hash table to get the capacity of
 * @return integer representing the capacity of the hash table, or RETURN_FAILURE on failure
 */
int hash_table_capacity(const HashTable* table);

/**
 * @brief gets an array of all keys in the hash table
 * 
 * Returns an array of all keys in the hash table.
 * The array is allocated on the heap and must be freed by the caller.
 * 
 * @param table The hash table to get the keys from
 * @return void** corresponding to an array of keys in the hash table, or NULL on failure
 */
void** hash_table_keyset(const HashTable* table);

/**
 * @brief frees the hash table and all associated memory
 * 
 * Frees the hash table and all associated memory. Does not free the keys or values themselves.
 * 
 * @param table The hash table to free
 */
void hash_table_free(HashTable* table);

// Extended hash table operations

/**
 * @brief gets the current load factor of the hash table
 * 
 * Returns the current load factor of the hash table (size / capacity).
 * 
 * @param table The hash table to get the load factor of
 * @return float representing the load factor of the hash table, or RETURN_FAILURE on failure
 */
float hash_table_load_factor(const HashTable* table);

/**
 * @brief replaces the value for a given key
 * 
 * Replaces the value for a given key in the hash table.
 * If the key does not exist, the key-value pair is inserted.
 * 
 * @param table The hash table to replace in
 * @param key The key to replace
 * @param new_value The new value to insert
 */
void hash_table_replace(const HashTable* table, const void* key, const void* new_value);

/**
 * @brief clears all elements from the hash table
 * 
 * Clears all elements from the hash table, freeing all associated memory.
 * Does not free the keys or values themselves.
 * Does not free the bucket array itself, either.
 * 
 * @param table The hash table to clear
 */
void hash_table_clear(HashTable* table);

/**
 * @brief maps a function over all key-value pairs in the hash table
 * 
 * Maps a function over all key-value pairs in the hash table.
 * Both the key and value are passed to the function.
 * 
 * @param table The hash table to map over
 * @param func The function to map: should take two generic pointers (key, value)
 */
void hash_table_map(const HashTable* table, void (*func)(const void* key, const void* value));

/**
 * @brief gets an array of all values in the hash table
 * 
 * Returns an array of all values in the hash table. The array is allocated on the heap and must be freed by the caller.
 * 
 * @param table The hash table to get the values from
 * @return void** corresponding to an array of values in the hash table, or NULL on failure
 */
void** hash_table_values(const HashTable* table);

/**
 * @brief checks if two hash tables are equal
 * 
 * Checks if two hash tables are equal. Returns 1 if the hash tables are equal, 0 otherwise.
 * 
 * @param table1 The first hash table to compare
 * @param table2 The second hash table to compare
 * @param compare The comparison function for values: should return 0 if values are equal, non-zero otherwise
 * @return integer 1 if the hash tables are equal, 0 if they are not, or RETURN_FAILURE on failure
 */
int hash_table_equals(const HashTable* table1, const HashTable* table2, int (*compare)(const void*, const void*));

/**
 * @brief copies a hash table
 * 
 * Copies a hash table, creating a new hash table with the same keys and values.
 * All keys and values are copied by reference, not by value.
 * 
 * @param table 
 * @return HashTable* corresponding to the copied hash table, or NULL on failure
 */
HashTable* hash_table_copy(const HashTable* table);

/**
 * @brief merges two hash tables
 * 
 * Merges two hash tables, copying all key-value pairs from the source table to the destination table.
 * If a key already exists in the destination table, the value is replaced.
 * 
 * @param dest The destination hash table
 * @param source The source hash table
 */
void hash_table_merge(HashTable* dest, const HashTable* source);

#endif // _HASHTABLE_H_