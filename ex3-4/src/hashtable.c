#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

// Node structure for each key-value pair in the hash table
struct HashNode {
    void* key;
    void* value;
    struct HashNode* next;

};

// HashTable structure definition
struct HashTable {
    HashNode** buckets;
    int size;
    int capacity;
    int (*compare)(const void*, const void*);
    unsigned long (*hash_func)(const void*);

};

// Helper function to create a new hash node
static HashNode* create_node(
    void* key,
    void* value
) {
    HashNode* node = malloc(sizeof(HashNode));
    if (!node)
        return NULL;

    node -> key = key;
    node -> value = value;
    node -> next = NULL;

    return node;
}

// Hash table creation function
HashTable* hash_table_create(
    int (*compare)(const void*, const void*), 
    unsigned long (*hash_func)(const void*)
) {
    HashTable* table = malloc(sizeof(HashTable));
    if (!table)
        return NULL;

    table -> capacity = 101;  // Initial capacity, prime number for better distribution
    table -> size = 0;
    table -> compare = compare;
    table -> hash_func = hash_func;
    table -> buckets = calloc(table -> capacity, sizeof(HashNode*));

    if (!table -> buckets) {
        free(table);
        return NULL;
    }

    return table;
}

// Insert or update a key-value pair in the hash table
void hash_table_put(
    HashTable* table,
    void* key,
    void* value
) {
    unsigned long index = table -> hash_func(key) % table -> capacity;
    HashNode* node = table -> buckets[index];

    // Search for the node with the same key
    while (node) {
        if (table -> compare(node -> key, key) == 0) {
            node -> value = (void*)value; // Update the value if the key already exists
            return;
        }

        node = node -> next;
    }

    // Key does not exist, create a new node
    HashNode* new_node = create_node(key, value);
    new_node -> next = table -> buckets[index];
    table -> buckets[index] = new_node;
    table -> size++;
}

// Retrieve a value from the hash table by key
void* hash_table_get(const HashTable* table, const void* key) {
    unsigned long index = table -> hash_func(key) % table -> capacity;
    HashNode* node = table -> buckets[index];

    while (node) {
        if (table -> compare(node -> key, key) == 0)
            return node -> value;

        node = node -> next;
    }
    return NULL; // Key not found
}

// Check if a key exists in the hash table
int hash_table_contains_key(const HashTable* table, const void* key) {
    return hash_table_get(table, key) != NULL;
}

// Remove a key-value pair from the hash table
void hash_table_remove(HashTable* table, const void* key) {
    unsigned long index = table -> hash_func(key) % table -> capacity;
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

// Get the current number of key-value pairs in the hash table
int hash_table_size(const HashTable* table) {
    return table -> size;
}

// Get an array of all keys in the hash table
void** hash_table_keyset(const HashTable* table) {
    void** keys = malloc(table -> size * sizeof(void*));
    int idx = 0;
    HashNode* node;

    for (int i = 0; i < table -> capacity; i++) {
        node = table -> buckets[i];

        while (node) {
            keys[idx++] = node -> key;
            node = node -> next;
        }
    }
    return keys;
}

// Free all memory associated with the hash table
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

// Resize the hash table to a new capacity
void hash_table_resize(HashTable* table, int new_capacity) {
    HashNode** new_buckets = calloc(new_capacity, sizeof(HashNode*));
    if (!new_buckets)
        return;

    HashNode* node;
    HashNode* next_node;
    unsigned long new_index;

    for (int i = 0; i < table -> capacity; i++) {
        node = table -> buckets[i];

        while (node) {
            new_index = table -> hash_func(node -> key) % new_capacity;

            next_node = node -> next;
            node -> next = new_buckets[new_index];
            new_buckets[new_index] = node;
            node = next_node;
        }
    }

    free(table -> buckets);

    table -> buckets = new_buckets;
    table -> capacity = new_capacity;
}

// Calculate the load factor
float hash_table_load_factor(const HashTable* table) {
    return (float)table -> size / (float)table -> capacity;
}

// Replace the value associated with a key if it exists
void hash_table_replace(const HashTable* table, const void* key, const void* new_value) {
    unsigned long index = table -> hash_func(key) % table -> capacity;
    HashNode* node = table -> buckets[index];

    while (node) {
        if (table -> compare(node -> key, key) == 0) {
            node -> value = (void*)new_value;
            return;
        }

        node = node -> next;
    }
}

// Clear all elements in the hash table without deallocating the structure
void hash_table_clear(HashTable* table) {
    HashNode* node;
    HashNode* temp;

    for (int i = 0; i < table -> capacity; i++) {
        node = table -> buckets[i];

        while (node) {
            temp = node;
            node = node -> next;
            free(temp);
        }

        table -> buckets[i] = NULL;
    }

    table -> size = 0;
}

// Apply a function to each key-value pair in the hash table
void hash_table_map(const HashTable* table, void (*func)(void* key, void* value)) {
    HashNode* node;

    for (int i = 0; i < table -> capacity; i++) {
        node = table -> buckets[i];

        while (node) {
            func(node -> key, node -> value);
            node = node -> next;
        }
    }
}

// Get an array of all values in the hash table
void** hash_table_values(const HashTable* table) {
    void** values = malloc(table -> size * sizeof(void*));
    int idx = 0;
    HashNode* node;

    for (int i = 0; i < table -> capacity; i++) {
        node = table -> buckets[i];

        while (node) {
            values[idx++] = node -> value;
            node = node -> next;
        }
    }

    return values;
}

// Compare if two hash tables are equal (shallow comparison)
int hash_table_equals(const HashTable* table1, const HashTable* table2) {
    if (table1 -> size != table2 -> size
        || table1 -> capacity != table2 -> capacity)
        return 0;

    HashNode* node;
    const void* value;

    for (int i = 0; i < table1 -> capacity; i++) {
        node = table1 -> buckets[i];

        while (node) {
            value = hash_table_get(table2, node -> key);
            if (!value || table1 -> compare(value, node -> value) != 0)
                return 0;

            node = node -> next;
        }
    }

    return 1;
}

// Create a deep copy of the hash table
HashTable* hash_table_copy(const HashTable* table) {
    HashTable* new_table = hash_table_create(table -> compare, table -> hash_func);
    hash_table_resize(new_table, table -> capacity);

    HashNode* node;

    for (int i = 0; i < table -> capacity; i++) {
        node = table -> buckets[i];

        while (node) {
            hash_table_put(new_table, node -> key, node -> value);
            node = node -> next;
        }
    }

    return new_table;
}

// Merge two hash tables
void hash_table_merge(HashTable* dest, const HashTable* source) {
    HashNode* node;

    for (int i = 0; i < source -> capacity; i++) {
        node = source -> buckets[i];

        while (node) {
            hash_table_put(dest, node -> key, node -> value);
            node = node -> next;
        }
    }
}
