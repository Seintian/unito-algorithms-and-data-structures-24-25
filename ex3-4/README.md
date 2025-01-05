# laboratorio-algoritmi-2024-2025 - Exercise 3-4

## Implementation Choices

### Graph Data Structure

The graph is implemented using a hash table-based adjacency list. Each node in the graph is a key in a hash table, and the associated value is another hash table representing the neighboring nodes and their corresponding edges. The graph is structured as follows:

#### `Graph` Struct

The `Graph` struct represents the graph itself. It includes:

- `nodes`: A hash table where each key is a node, and the value is a hash table of adjacent nodes with their edges.
- `labelled`: A boolean flag indicating whether edges have labels.
- `directed`: A boolean flag indicating whether the graph is directed.
- `num_edges`: The total number of edges in the graph.
- `compare`: A pointer to a function that compares two elements.
- `hash`: A pointer to a function that computes the hash value of an element.

#### Adjancency List Implementation

The adjacency list is implemented as nested hash tables. For example:

```c
nodes = HashTable {
    "torino" -> HashTable {
        "savona" -> <struct Edge>,
        ...
    },
    ...
}
```

**Note**: it could have been implemented better by storing direct `labels` as values of the inner `HashTable` instead of entire `Edge` structs. We did so because we thought it was required by the project instructions.
Then, the optimal implementation we would have done is this:

```c
nodes = HashTable {
    "torino" -> HashTable {
        "savona" -> 3452345.7564,
        ...
    },
    ...
}
```

### Edge Addition Handling

The `graph_add_edge` function handles the addition of edges to the graph. The function operates differently for directed and undirected graphs:

- For _directed_ graphs, edges are only added in one direction.
- For _undirected_ graphs, edges are added in both directions, ensuring bidirectional connectivity.
- The function checks if an edge already exists between two nodes before adding it, preventing duplicate edges.

## Performance of BFS

The algorithm was executed on the dataset `italian_dist_graph.csv` with the following input:

- Source node: `torino`
- Output file: `output.txt`

### Execution Times

| Run | Time Taken |
|-----|------------|
|   1 |      0.017 |
|   2 |      0.015 |
|   3 |      0.017 |
|   4 |      0.014 |
|   5 |      0.014 |
|   6 |      0.017 |
|   7 |      0.016 |
|   8 |      0.014 |
|   9 |      0.017 |
|  10 |      0.016 |
|  11 |      0.016 |
|  12 |      0.016 |
|  13 |      0.016 |

### Observations

- The execution times were consistent, with minimal variations (**~0.003 seconds**).
- The observed times align well with expectations for an efficient adjacency list-based implementation.
- The average execution time across all runs is approximately **0.016 seconds**.

## Conclusion

The current implementation efficiently handles graph operations using a hash table-based adjacency list. The choice of using `Edge` structs directly simplifies edge handling, but an alternative approach of storing only edge labels could reduce memory usage, with the trade-off of slightly increased complexity in edge-related queries.
