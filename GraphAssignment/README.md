# Graph Assignment - C++ Implementation using Adjacency List

**Author:** Meir Shuker  
**Email:** meirshuker159@gmail.com  


---

## 📋 Assignment Overview

This project implements an **undirected weighted graph** using an **adjacency list representation** in C++ without using the Standard Template Library (STL). The implementation includes a comprehensive set of graph algorithms and custom data structures built from scratch using only basic arrays.

### 🎯 Assignment Goals
- Understanding C++ memory management
- Implementing classes, constructors, and destructors
- Working with namespaces and parameter passing
- Building data structures without STL
- Implementing fundamental graph algorithms

---

## 🏗️ Project Structure

```
GraphAssignment/
├── Include/                     # Header files
│   ├── Graph.h                 # Graph class declaration
│   ├── Algorithms.h            # Algorithms class declaration
│   ├── GraphException.h        # Custom exception class (STL-free)
│   └── data_structures/        # Custom data structure headers
│       ├── Queue.h             # FIFO Queue for BFS
│       ├── PriorityQueue.h     # Min-heap Priority Queue for Dijkstra/Prim
│       └── UnionFind.h         # Union-Find with path compression for Kruskal
├── src/                        # Implementation files
│   ├── Graph.cpp               # Graph class implementation
│   ├── Algorithms.cpp          # All graph algorithms implementation
│   └── data_structures/        # Custom data structure implementations
│       ├── Queue.cpp           # Circular array Queue implementation
│       ├── PriorityQueue.cpp   # Min-heap Priority Queue implementation
│       └── UnionFind.cpp       # Union-Find with optimizations implementation
├── Test/                       # Unit testing
│   ├── test_graph.cpp          # Comprehensive unit tests (10 test cases)
│   └── doctest.h               # Testing framework
├── main.cpp                    # Main demonstration program
├── Makefile                    # Build automation with valgrind support
└── README.md                   # This documentation file
```

---

## 🧠 Core Features

### 🔗 Graph Class (`graph::Graph`)
Located in the `graph` namespace, implements an undirected weighted graph with:

- **Fixed vertex count** - Set at initialization, cannot be changed
- **Adjacency list representation** - Using custom linked lists
- **Core operations:**
  - `addEdge(src, dest, weight=1)` - Add undirected edge with optional weight
  - `removeEdge(src, dest)` - Remove edge (throws exception if not found)
  - `print_graph()` - Display graph in readable format
  - `getVertexCount()` - Return number of vertices
  - `getNeighbors(vertex, count)` - Get neighbors as array

### 🧮 Algorithms Class (`graph::Algorithms`)
Implements classic graph algorithms:

- **`bfs(graph, start)`** - Breadth-First Search, returns BFS tree
- **`dfs(graph, start)`** - Depth-First Search, returns DFS tree/forest  
- **`dijkstra(graph, start)`** - Shortest path tree from source
- **`prim(graph)`** - Minimum Spanning Tree using Prim's algorithm
- **`kruskal(graph)`** - Minimum Spanning Tree using Kruskal's algorithm

### 🗂️ Custom Data Structures
All implemented without STL, using only basic arrays and manual memory management:

- **Queue** - FIFO circular array structure for BFS traversal
- **Priority Queue** - Min-heap implementation for Dijkstra and Prim algorithms
- **Union-Find** - Disjoint set with path compression and union by rank for Kruskal's algorithm
- **GraphException** - Custom exception class replacing all STL exceptions

---

## 🛠️ Building and Running

### Prerequisites
- g++ compiler with C++11 support
- make utility
- valgrind (for memory leak detection)

### Build Commands

```bash
# Build main demonstration program
make Main

# Build and run unit tests
make test

# Check for memory leaks
make valgrind

# Clean build artifacts
make clean
```

---

## 🧪 Testing

The project includes comprehensive unit tests using the **doctest** framework:

- **Graph operations testing** - Add/remove edges, vertex management, boundary conditions
- **Data structures testing** - Queue, PriorityQueue, UnionFind functionality
- **Algorithm correctness** - BFS, DFS, shortest paths, MST algorithms
- **Exception handling** - Custom GraphException for all error conditions
- **Edge cases** - Disconnected graphs, single vertex, algorithm robustness
- **Memory management** - No memory leaks (verified with valgrind)



---

## 📊 Example Usage

```cpp
#include "Include/Graph.h"
#include "Include/Algorithms.h"
using namespace graph;

int main() {
    // Create graph with 5 vertices
    Graph g(5);
    
    // Add weighted edges
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 2, 2);
    
    // Run algorithms
    Graph bfsTree = Algorithms::bfs(g, 0);
    Graph mst = Algorithms::prim(g);
    
    // Display results
    g.print_graph();
    bfsTree.print_graph();
    
    return 0;
}
```

---

## ⚡ Performance Characteristics

| Algorithm | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| BFS       | O(V + E)       | O(V)            |
| DFS       | O(V + E)       | O(V)            |
| Dijkstra  | O(V²)          | O(V)            |
| Prim      | O(V²)          | O(V)            |
| Kruskal   | O(E log E)     | O(V)            |

*Note: Optimizations possible with more sophisticated heap implementations*

---

## 🔧 Design Decisions

### Memory Management
- **Manual memory allocation** using `new` and `delete`
- **RAII principle** - Resources managed by constructors/destructors
- **Exception safety** - Proper cleanup in error cases

### Data Structure Choice
- **Adjacency List** - Efficient for sparse graphs
- **Linked Lists** - Dynamic neighbor storage
- **Array-based implementations** - Meeting STL restriction requirements

### Algorithm Implementation
- **Static methods** - Algorithms don't maintain state
- **Return by value** - New graph objects for results
- **Consistent interface** - All algorithms follow same pattern

---

## 🚀 Key Technical Achievements

- ✅ **Complete STL independence** - Zero STL containers or utilities used
- ✅ **Custom exception system** - GraphException replaces all STL exceptions
- ✅ **Memory leak free** - Verified with valgrind, perfect memory management
- ✅ **Exception safe** - Robust error handling with custom exceptions
- ✅ **Modular design** - Clean separation of concerns and namespaces
- ✅ **Comprehensive testing** - 10 test cases with 64 assertions covering edge cases
- ✅ **Algorithm correctness** - All graph algorithms properly implemented and verified
- ✅ **Standard compliance** - C++11 compatible code following best practices

---

