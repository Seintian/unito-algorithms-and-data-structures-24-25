#include "hashtable.h"
#include "prime.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define INITIAL_CAPACITY 16 // It will be 17 after `next_prime(INITIAL_CAPACITY)`
#define LOAD_FACTOR_UP_THRESHOLD 0.7f
#define LOAD_FACTOR_DOWN_THRESHOLD 0.2f

struct HashNode {
    const void* key;
    const void* value;
    HashNode* next;
};

struct HashTable {
    HashNode** buckets;
    int capacity;
    int size;
    int (*compare)(const void*, const void*);
    unsigned long (*hash_func)(const void*);
};

// Helper functions
static HashNode* hash_node_create(const void* key, const void* value);
static HashTable* hash_table_create_sized(
    int (*compare)(const void*, const void*),
    unsigned long (*hash_func)(const void*),
    int base_capacity
);
static void hash_table_resize(HashTable* table, int new_capacity);

// Function to create a new HashNode
static HashNode* hash_node_create(const void* key, const void* value) {
    HashNode* node = malloc(sizeof(HashNode));
    if (!node)
        return NULL;

    node -> key = key;
    node -> value = value;
    node -> next = NULL;

    return node;
}

// Function to create a new hash table with a specified capacity
static HashTable* hash_table_create_sized(
    int (*compare)(const void*, const void*),
    unsigned long (*hash_func)(const void*),
    int base_capacity
) {
    HashTable* table = malloc(sizeof(HashTable));
    if (!table)
        return NULL;

    table -> buckets = (HashNode**) calloc(base_capacity, sizeof(HashNode*));
    if (!table -> buckets) {
        free(table);
        return NULL;
    }

    table -> capacity = next_prime(base_capacity);
    table -> size = 0;
    table -> compare = compare;
    table -> hash_func = hash_func;

    return table;
}

// Function to resize the hash table
static void hash_table_resize(HashTable* table, int new_capacity) {
    if (new_capacity < INITIAL_CAPACITY)
        return;
    
    HashTable* new_table = hash_table_create_sized(table -> compare, table -> hash_func, new_capacity);
    if (!new_table)
        return;

    for (int i = 0; i < table -> capacity; i++) {
        HashNode* node = table -> buckets[i];

        while (node) {
            // Create a new copy of the node to preserve the original
            HashNode* next_node = node -> next; // Save next pointer before modifying
            unsigned long new_hash = table -> hash_func(node -> key);
            int new_index = new_hash % new_table -> capacity;

            // Insert directly into the new table's bucket (prevents using `hash_table_put`)
            node -> next = new_table -> buckets[new_index];
            new_table -> buckets[new_index] = node;

            node = next_node;
        }
    }

    hash_table_clear(table); // Free nodes but not `buckets` pointer
    free(table -> buckets);    // Free the old buckets array safely

    table -> buckets = new_table -> buckets;
    table -> capacity = new_table -> capacity;

    free(new_table); // Only free the `HashTable` structure, not `buckets`
}

// Function to create a new hash table
HashTable* hash_table_create(int (*compare)(const void*, const void*), unsigned long (*hash_func)(const void*)) {
    return hash_table_create_sized(compare, hash_func, INITIAL_CAPACITY);
}

// Basic hash table operations
void hash_table_put(HashTable* table, const void* key, const void* value) {
    if (hash_table_load_factor(table) > LOAD_FACTOR_UP_THRESHOLD)
        hash_table_resize(table, table -> capacity * 2);

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
    if (hash_table_load_factor(table) < LOAD_FACTOR_DOWN_THRESHOLD)
        hash_table_resize(table, table -> capacity / 2);

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
    return hash_table_get(table, key) != NULL;
}

int hash_table_size(const HashTable* table) {
    return table -> size;
}

int hash_table_capacity(const HashTable* table) {
    return table -> capacity;
}

void** hash_table_keyset(const HashTable* table) {
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
    if (table == NULL || hash_table_size(table) == 0)
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
    hash_table_clear(table);

    if (table -> buckets)
        free(table -> buckets);

    free(table);
}

// Extended hash table operations
float hash_table_load_factor(const HashTable* table) {
    return (float) table -> size / (float) table -> capacity;
}

void hash_table_replace(const HashTable* table, const void* key, const void* new_value) {
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
    for (int i = 0; i < table -> capacity; i++) {
        HashNode* node = table -> buckets[i];

        while (node) {
            func(node -> key, node -> value);
            node = node -> next;
        }
    }
}

void** hash_table_values(const HashTable* table) {
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

int hash_table_equals(const HashTable* table1, const HashTable* table2) {
    if (table1 -> size != table2 -> size)
        return 0;

    for (int i = 0; i < table1 -> capacity; i++) {
        HashNode* node = table1 -> buckets[i];

        while (node) {
            if (table1 -> compare(node -> key, hash_table_get(table2, node -> key)) != 0)
                return 0;

            node = node -> next;
        }
    }

    return 1;
}

void hash_table_merge(HashTable* dest, const HashTable* source) {
    for (int i = 0; i < source -> capacity; i++) {
        HashNode* node = source -> buckets[i];

        while (node) {
            hash_table_put(dest, node -> key, node -> value);
            node = node -> next;
        }
    }
}

HashTable* hash_table_copy(const HashTable* table) {
    HashTable* new_table = hash_table_create(table -> compare, table -> hash_func);
    if (!new_table)
        return NULL;

    hash_table_merge(new_table, table);

    return new_table;
}