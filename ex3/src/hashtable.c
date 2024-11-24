/**
 * @file hashtable.c
 * @brief Implementation of a generic hash table data structure.
 */

#include "error_logger.h"
#include "hashtable.h"
#include "prime.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/** @brief Initial capacity for the hash table. 
 * 
 * The initial capacity for the hash table.
 * The actual capacity will be the next prime number after this value.
*/
#define INITIAL_CAPACITY 16

/** @brief Upper load factor threshold for resizing the table up. */
#define LOAD_FACTOR_UP_THRESHOLD 0.7f

/** @brief Upper load factor tolerance to continue hash_table_put() if hash_table_resize() fails */
#define LOAD_FACTOR_UP_TOLERANCE 1.0f

/** @brief Lower load factor threshold for resizing the table down. */
#define LOAD_FACTOR_DOWN_THRESHOLD 0.2f

/**
 * @struct HashNode
 * @brief Node structure to represent an entry in the hash table.
 * 
 * @var HashNode::key
 * The key of the entry.
 * @var HashNode::value
 * The value associated with the key.
 * @var HashNode::next
 * Pointer to the next node in case of collisions (linked list).
 */
struct HashNode {
    const void* key;
    const void* value;
    HashNode* next;
};

/**
 * @struct HashTable
 * @brief Structure to represent the hash table.
 * 
 * @var HashTable::buckets
 * Array of pointers to hash nodes (buckets).
 * @var HashTable::capacity
 * The current capacity of the hash table.
 * @var HashTable::size
 * The current number of elements in the hash table.
 * @var HashTable::compare
 * Function pointer for comparing keys.
 * @var HashTable::hash_func
 * Function pointer for hashing keys.
 */
struct HashTable {
    HashNode** buckets;
    int capacity;
    int size;
    int (*compare)(const void*, const void*);
    unsigned long (*hash_func)(const void*);
};

// Helper functions

/**
 * @brief Creates a new hash node.
 * 
 * @param key Pointer to the key.
 * @param value Pointer to the value.
 * @return Pointer to the created hash node, or NULL if memory allocation fails.
 */
static HashNode* hash_node_create(const void* key, const void* value);

/**
 * @brief Creates a new hash table with a specified base capacity.
 * 
 * @param compare Function pointer for comparing keys.
 * @param hash_func Function pointer for hashing keys.
 * @param base_capacity The base capacity for the new hash table.
 * @return Pointer to the created hash table, or NULL if memory allocation fails.
 */
static HashTable* hash_table_create_sized(
    int (*compare)(const void*, const void*),
    unsigned long (*hash_func)(const void*),
    int base_capacity
);

/**
 * @brief Resizes the hash table to a new capacity.
 * 
 * @param table Pointer to the hash table.
 * @param new_capacity The new capacity to resize to.
 * @return RETURN_FAILURE on failure, RETURN_SUCCESS on success
 */
static ReturnType hash_table_resize(HashTable* table, int new_capacity);

static HashNode* hash_node_create(const void* key, const void* value) {
    HashNode* node = malloc(sizeof(HashNode));
    if (!node)
        return NULL;

    node -> key = key;
    node -> value = value;
    node -> next = NULL;

    return node;
}

static HashTable* hash_table_create_sized(
    int (*compare)(const void*, const void*),
    unsigned long (*hash_func)(const void*),
    int base_capacity
) {
    HashTable* table = malloc(sizeof(HashTable));
    if (!table)
        return NULL;

    table -> capacity = next_prime(base_capacity);
    table -> size = 0;
    table -> compare = compare;
    table -> hash_func = hash_func;

    table -> buckets = (HashNode**) calloc(table -> capacity, sizeof(HashNode*));
    if (!table -> buckets) {
        free(table);

        return NULL;
    }

    return table;
}

static ReturnType hash_table_resize(HashTable* table, int new_capacity) {
    new_capacity = next_prime(new_capacity);
    
    HashNode** new_buckets = (HashNode**) calloc(new_capacity, sizeof(HashNode*));
    if (!new_buckets)
        return RETURN_FAILURE;

    for (int i = 0; i < table -> capacity; i++) {
        HashNode* node = table -> buckets[i];

        while (node) {
            HashNode* next_node = node -> next;
            unsigned long new_hash = table -> hash_func(node -> key);
            int new_index = new_hash % new_capacity;

            node -> next = new_buckets[new_index];
            new_buckets[new_index] = node;

            node = next_node;
        }
    }

    free(table -> buckets);
    table -> buckets = new_buckets;
    table -> capacity = new_capacity;

    return RETURN_SUCCESS;
}

HashTable* hash_table_create(int (*compare)(const void*, const void*), unsigned long (*hash_func)(const void*)) {
    return hash_table_create_sized(compare, hash_func, INITIAL_CAPACITY);
}

// Basic hash table operations

void hash_table_put(HashTable* table, const void* key, const void* value) {
    if (table == NULL)
        raise_error("Hash table is NULL.");
    
    float load_factor = hash_table_load_factor(table);
    if (
        load_factor > LOAD_FACTOR_UP_THRESHOLD
        && hash_table_resize(table, table -> capacity * 2) == RETURN_FAILURE 
        && load_factor > LOAD_FACTOR_UP_TOLERANCE
    )
        raise_error("Hash table is too full and resizing failed.");

    unsigned long hash = table -> hash_func(key) % table -> capacity;
    HashNode* node = table -> buckets[hash];

    while (node) {
        if (table -> compare(node -> key, key) == 0) {
            node -> value = value;
            return;
        }

        node = node -> next;
    }

    HashNode* new_node = hash_node_create(key, value);
    if (!new_node)
        return;

    new_node -> next = table -> buckets[hash];
    table -> buckets[hash] = new_node;
    table -> size++;
}

void hash_table_remove(HashTable* table, const void* key) {
    if (table == NULL)
        raise_error("Hash table is NULL.");

    if (
        hash_table_load_factor(table) < LOAD_FACTOR_DOWN_THRESHOLD
        && table -> capacity / 2 >= INITIAL_CAPACITY
        && hash_table_resize(table, table -> capacity / 2) == RETURN_FAILURE
    )
        raise_error("Hash table is too empty and resizing failed.");

    unsigned long hash = table -> hash_func(key);
    int index = hash % table -> capacity;
    HashNode* node = table -> buckets[index];
    HashNode* prev = NULL;

    while (node) {
        if (table -> compare(node -> key, key) == 0) {
            if (prev)
                prev -> next = node -> next;

            else
                table -> buckets[index] = node -> next;

            free(node);
            table -> size--;

            return;
        }

        prev = node;
        node = node -> next;
    }
}

void* hash_table_get(const HashTable* table, const void* key) {
    if (table == NULL)
        return NULL;

    unsigned long hash = table -> hash_func(key);
    int index = hash % table -> capacity;
    HashNode* node = table -> buckets[index];

    while (node) {
        if (table -> compare(node -> key, key) == 0)
            return (void*) node -> value;

        node = node -> next;
    }

    return NULL;
}

int hash_table_contains_key(const HashTable* table, const void* key) {
    if (table == NULL)
        return RETURN_FAILURE;

    return hash_table_get(table, key) != NULL;
}

int hash_table_size(const HashTable* table) {
    if (table == NULL)
        return RETURN_FAILURE;

    return table -> size;
}

int hash_table_capacity(const HashTable* table) {
    if (table == NULL)
        return RETURN_FAILURE;

    return table -> capacity;
}

void** hash_table_keyset(const HashTable* table) {
    if (table == NULL)
        return NULL;

    void** keys = (void**) calloc(table -> size, sizeof(void*));
    if (!keys)
        return NULL;

    int index = 0;
    for (int i = 0; i < table -> capacity; i++) {
        HashNode* node = table -> buckets[i];

        while (node) {
            keys[index++] = (void*) node -> key;
            node = node -> next;
        }
    }

    return keys;
}

void hash_table_clear(HashTable* table) {
    if (table == NULL)
        raise_error("Hash table is NULL.");

    if (hash_table_size(table) == 0)
        return;

    for (int i = 0; i < table -> capacity; i++) {
        HashNode* node = table -> buckets[i];

        while (node) {
            HashNode* next = node -> next;
            free(node);
            node = next;
        }

        table -> buckets[i] = NULL;
    }

    table -> size = 0;
}

void hash_table_free(HashTable* table) {
    if (table == NULL)
        raise_error("Hash table is NULL.");

    hash_table_clear(table);
    free(table -> buckets);
    free(table);
}

// Extended hash table operations

float hash_table_load_factor(const HashTable* table) {
    if (table == NULL)
        return (float) RETURN_FAILURE;

    return (float) table -> size / (float) table -> capacity;
}

void hash_table_replace(const HashTable* table, const void* key, const void* new_value) {
    if (table == NULL)
        raise_error("Hash table is NULL.");

    unsigned long hash = table -> hash_func(key);
    int index = hash % table -> capacity;
    HashNode* node = table -> buckets[index];

    while (node) {
        if (table -> compare(node -> key, key) == 0) {
            node -> value = new_value;
            return;
        }

        node = node -> next;
    }
}

void hash_table_map(const HashTable* table, void (*func)(const void* key, const void* value)) {
    if (table == NULL)
        raise_error("Hash table is NULL.");

    for (int i = 0; i < table -> capacity; i++) {
        HashNode* node = table -> buckets[i];

        while (node) {
            func(node -> key, node -> value);
            node = node -> next;
        }
    }
}

void** hash_table_values(const HashTable* table) {
    if (table == NULL)
        return NULL;

    void** values = (void**) calloc(table -> size, sizeof(void*));
    if (!values)
        return NULL;

    int index = 0;
    for (int i = 0; i < table -> capacity; i++) {
        HashNode* node = table -> buckets[i];

        while (node) {
            values[index++] = (void*) node -> value;
            node = node -> next;
        }
    }

    return values;
}

int hash_table_equals(
    const HashTable* table1,
    const HashTable* table2,
    int (*compare)(const void*, const void*)
) {
    if (table1 == NULL || table2 == NULL)
        return RETURN_FAILURE;

    if (table1 -> size != table2 -> size)
        return 0;

    for (int i = 0; i < table1 -> capacity; i++) {
        HashNode* node = table1 -> buckets[i];
        HashNode* node2 = table2 -> buckets[i];

        while (node && node2) {
            if (table1 -> compare(node -> key, node2 -> key) != 0)
                return 0;

            if (compare(node -> value, node2 -> value) != 0)
                return 0;

            node = node -> next;
            node2 = node2 -> next;
        }
    }

    return 1;
}

void hash_table_merge(HashTable* dest, const HashTable* source) {
    if (dest == NULL || source == NULL)
        raise_error("Hash table is NULL.");

    for (int i = 0; i < source -> capacity; i++) {
        HashNode* node = source -> buckets[i];

        while (node) {
            hash_table_put(dest, node -> key, node -> value);
            node = node -> next;
        }
    }
}

HashTable* hash_table_copy(const HashTable* table) {
    if (table == NULL)
        return NULL;

    HashTable* new_table = hash_table_create(table -> compare, table -> hash_func);
    if (!new_table)
        return NULL;

    hash_table_merge(new_table, table);

    return new_table;
}