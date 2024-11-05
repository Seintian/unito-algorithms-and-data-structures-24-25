#include "hashtable.h"
#include <stdlib.h>
#include <string.h>


#define INITIAL_CAPACITY 16
#define LOAD_FACTOR_THRESHOLD 0.75f

struct HashNode {
    const void* key;
    const void* value;
    struct HashNode* next;
};

struct HashTable {
    HashNode** buckets;
    int capacity;
    int size;
    int (*compare)(const void*, const void*);
    unsigned long (*hash_func)(const void*);
};

// Helper function to create a new HashNode
static HashNode* hash_node_create(const void* key, const void* value) {
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    if (!node)
        return NULL;

    node -> key = key;
    node -> value = value;
    node -> next = NULL;

    return node;
}

// Function to create a new hash table
HashTable* hash_table_create(int (*compare)(const void*, const void*), unsigned long (*hash_func)(const void*)) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (!table)
        return NULL;

    table -> buckets = (HashNode**)calloc(INITIAL_CAPACITY, sizeof(HashNode*));
    if (!table -> buckets) {
        free(table);
        return NULL;
    }

    table -> capacity = INITIAL_CAPACITY;
    table -> size = 0;
    table -> compare = compare;
    table -> hash_func = hash_func;

    return table;
}

// Function to resize the hash table
static void hash_table_resize(HashTable* table) {
    int new_capacity = table -> capacity * 2;
    HashNode** new_buckets = (HashNode**)calloc(new_capacity, sizeof(HashNode*));
    
    for (int i = 0; i < table -> capacity; i++) {
        HashNode* node = table -> buckets[i];

        while (node) {
            HashNode* next = node -> next;
            unsigned long hash = table -> hash_func(node -> key) % new_capacity; // Rehash with new capacity

            // Insert the node into the new buckets
            node -> next = new_buckets[hash];
            new_buckets[hash] = node;

            node = next;
        }
    }
    
    free(table -> buckets);
    table -> buckets = new_buckets;
    table -> capacity = new_capacity;
}

// Insert or update a key-value pair
void hash_table_put(HashTable* table, const void* key, const void* value) {
    unsigned long hash = table -> hash_func(key) % table -> capacity;
    HashNode* node = table -> buckets[hash];
    HashNode* prev = NULL;

    // Check if key exists, update if so
    while (node) {
        if (table -> compare(node -> key, key) == 0) {
            node -> value = value;
            return;
        }

        prev = node;
        node = node -> next;
    }

    // Insert a new node
    HashNode* new_node = hash_node_create(key, value);
    if (prev)
        prev -> next = new_node;

    else
        table -> buckets[hash] = new_node;

    table -> size++;

    // Check load factor and resize if necessary
    if (hash_table_load_factor(table) > LOAD_FACTOR_THRESHOLD)
        hash_table_resize(table);
}

// Retrieve a value by key
void* hash_table_get(const HashTable* table, const void* key) {
    unsigned long hash = table -> hash_func(key) % table -> capacity;
    HashNode* node = table -> buckets[hash];

    while (node) {
        if (table -> compare(node -> key, key) == 0)
            return (void*)node -> value;

        node = node -> next;
    }
    return NULL;
}

// Check if a key exists
int hash_table_contains_key(const HashTable* table, const void* key) {
    return hash_table_get(table, key) != NULL;
}

// Remove a key-value pair
void hash_table_remove(HashTable* table, const void* key) {
    unsigned long hash = table -> hash_func(key) % table -> capacity;
    HashNode* node = table -> buckets[hash];
    HashNode* prev = NULL;

    while (node) {
        if (table -> compare(node -> key, key) == 0) {
            if (prev)
                prev -> next = node -> next;
            else
                table -> buckets[hash] = node -> next;

            free(node);
            table -> size--;
            return;
        }

        prev = node;
        node = node -> next;
    }
}

// Get the current size of the hash table
int hash_table_size(const HashTable* table) {
    return table -> size;
}

// Get the current capacity of the hash table
int hash_table_capacity(const HashTable* table) {
    return table -> capacity;
}

// Get an array of all keys
void** hash_table_keyset(const HashTable* table) {
    void** keys = (void**)malloc(table -> size * sizeof(void*));
    if (!keys)
        return NULL;

    int index = 0;
    for (int i = 0; i < table -> capacity; i++) {
        HashNode* node = table -> buckets[i];

        while (node) {
            keys[index++] = (void*)node -> key;
            node = node -> next;
        }
    }

    return keys;
}

// Free the entire hash table
void hash_table_free(HashTable* table) {
    for (int i = 0; i < table -> capacity; i++) {
        HashNode* node = table -> buckets[i];

        while (node) {
            HashNode* temp = node;
            node = node -> next;
            free(temp);
        }
    }

    free(table -> buckets);
    free(table);
}

// Calculate the current load factor
float hash_table_load_factor(const HashTable* table) {
    return (float)table -> size / (float)table -> capacity;
}

// Replace the value for an existing key
void hash_table_replace(const HashTable* table, const void* key, const void* new_value) {
    unsigned long hash = table -> hash_func(key) % table -> capacity;
    HashNode* node = table -> buckets[hash];

    while (node) {
        if (table -> compare(node -> key, key) == 0) {
            node -> value = new_value;
            return;
        }

        node = node -> next;
    }
}

// Clear all elements from the hash table
void hash_table_clear(HashTable* table) {
    for (int i = 0; i < table -> capacity; i++) {
        HashNode* node = table -> buckets[i];

        while (node) {
            HashNode* temp = node;
            node = node -> next;
            free(temp);
        }

        table -> buckets[i] = NULL;
    }

    table -> size = 0;
}

// Apply a function to each key-value pair
void hash_table_map(const HashTable* table, void (*func)(const void* key, const void* value)) {
    for (int i = 0; i < table -> capacity; i++) {
        HashNode* node = table -> buckets[i];

        while (node) {
            func(node -> key, node -> value);
            node = node -> next;
        }
    }
}

// Get an array of all values
void** hash_table_values(const HashTable* table) {
    void** values = (void**)malloc(table -> size * sizeof(void*));
    if (!values)
        return NULL;

    int index = 0;
    for (int i = 0; i < table -> capacity; i++) {
        HashNode* node = table -> buckets[i];

        while (node) {
            values[index++] = (void*)node -> value;
            node = node -> next;
        }
    }

    return values;
}

// Check if two hash tables are equal
int hash_table_equals(const HashTable* table1, const HashTable* table2) {
    if (table1 -> size != table2 -> size)
        return 0;

    for (int i = 0; i < table1 -> capacity; i++) {
        HashNode* node1 = table1 -> buckets[i];

        while (node1) {
            const void* value2 = hash_table_get(table2, node1 -> key);
            if (!value2 || table1 -> compare(node1 -> value, value2) != 0)
                return 0;

            node1 = node1 -> next;
        }
    }

    return 1;
}

// Create a deep copy of the hash table
HashTable* hash_table_copy(const HashTable* table) {
    HashTable* copy = hash_table_create(table -> compare, table -> hash_func);
    if (!copy)
        return NULL;

    for (int i = 0; i < table -> capacity; i++) {
        HashNode* node = table -> buckets[i];

        while (node) {
            hash_table_put(copy, node -> key, node -> value);
            node = node -> next;
        }
    }

    return copy;
}

// Merge two hash tables
void hash_table_merge(HashTable* dest, const HashTable* source) {
    for (int i = 0; i < source -> capacity; i++) {
        HashNode* node = source -> buckets[i];

        while (node) {
            hash_table_put(dest, node -> key, node -> value);
            node = node -> next;
        }
    }
}
