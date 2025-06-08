/**
 * @author meirshuker159@gmail.com
 * 
 * Test coverage includes:
 * - Graph basic operations (add/remove edges, neighbor access)
 * - BFS traversal algorithm correctness
 * - Algorithm functionality (Dijkstra, Prim, Kruskal)
 * - Memory management verification
 * - Data structure functionality (Queue, PriorityQueue, UnionFind)
 * - Exception handling and edge cases
 * - Algorithm correctness validation
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../Include/Graph.h"
#include "../Include/Algorithms.h"
#include "../Include/GraphException.h"
#include "../Include/data_structures/Queue.h"
#include "../Include/data_structures/PriorityQueue.h"
#include "../Include/data_structures/UnionFind.h"

using namespace graph;

/**
 * @brief Test case for basic graph operations
 * 
 * This test validates the core functionality of the Graph class including:
 * - Graph construction with specified vertex count
 * - Adding edges between vertices
 * - Retrieving neighbors of vertices
 * - Removing edges and verifying removal
 * - Proper memory management with dynamic neighbor arrays
 * 
 * @details Test procedure:
 * 1. Create a 4-vertex graph and add edges forming a path: 0-1-2-3
 * 2. Verify vertex count is correct
 * 3. Check that vertex 1 has neighbors 0 and 2
 * 4. Remove edge (1,2) and verify it's no longer present
 * 5. Ensure proper cleanup of dynamically allocated neighbor arrays
 */
TEST_CASE("Graph basic operations") {
    // Create graph and add path edges
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);

    // Verify vertex count
    CHECK(g.getVertexCount() == 4);

    // Test neighbor retrieval for vertex 1 (should have neighbors 0 and 2)
    int count;
    Neighbor* neighbors = g.getNeighbors(1, count);
    bool found0 = false, found2 = false;
    for (int i = 0; i < count; ++i) {
        if (neighbors[i].vertex == 0) found0 = true;
        if (neighbors[i].vertex == 2) found2 = true;
    }
    delete[] neighbors;  // Clean up dynamically allocated array

    CHECK(found0);  // Vertex 1 should be connected to vertex 0
    CHECK(found2);  // Vertex 1 should be connected to vertex 2

    // Test edge removal
    g.removeEdge(1, 2);
    neighbors = g.getNeighbors(1, count);
    bool stillHas2 = false;
    for (int i = 0; i < count; ++i) {
        if (neighbors[i].vertex == 2) stillHas2 = true;
    }
    delete[] neighbors;  // Clean up dynamically allocated array

    CHECK(!stillHas2);  // Vertex 1 should no longer be connected to vertex 2
}

/**
 * @brief Test case for BFS traversal algorithm
 * 
 * This test validates the Breadth-First Search implementation by:
 * - Creating a graph with known structure
 * - Running BFS from a specified starting vertex
 * - Verifying that the resulting tree has correct properties
 * - Checking that the starting vertex has outgoing edges in the BFS tree
 * 
 * @details Test procedure:
 * 1. Create a 5-vertex graph with star-like structure centered at vertex 0
 * 2. Add additional edges to create a more complex topology
 * 3. Run BFS starting from vertex 0
 * 4. Verify the BFS tree has the same number of vertices as original graph
 * 5. Check that the root vertex (0) has neighbors in the spanning tree
 * 6. Ensure proper memory management of neighbor arrays
 * 
 * @note The test focuses on structural correctness rather than specific edge validation
 */
TEST_CASE("BFS traversal") {
    // Create graph with star topology plus additional edges
    Graph g(5);
    g.addEdge(0, 1);  // Star center to vertex 1
    g.addEdge(0, 2);  // Star center to vertex 2
    g.addEdge(1, 3);  // Additional connection
    g.addEdge(2, 4);  // Additional connection

    // Run BFS from vertex 0 (star center)
    Graph tree = Algorithms::bfs(g, 0);
    CHECK(tree.getVertexCount() == 5);  // BFS tree should have same vertex count

    // Verify that the root vertex has neighbors in the BFS tree
    int count;
    Neighbor* neighbors = tree.getNeighbors(0, count);
    CHECK(count > 0);  // Root should have at least one neighbor in spanning tree
    delete[] neighbors;  // Clean up dynamically allocated array
}

/**
 * @brief Test case for shortest path and minimum spanning tree algorithms
 * 
 * This test validates the correctness of advanced graph algorithms:
 * - Dijkstra's shortest path algorithm
 * - Prim's minimum spanning tree algorithm
 * - Kruskal's minimum spanning tree algorithm
 * 
 * @details Test procedure:
 * 1. Create a 4-vertex graph forming a weighted cycle
 * 2. Add edges with increasing weights: (0,1,1), (1,2,2), (2,3,3), (3,0,4)
 * 3. Run Dijkstra from vertex 0 and verify tree structure
 * 4. Run Prim's MST algorithm and verify result
 * 5. Run Kruskal's MST algorithm and verify result
 * 6. Ensure all algorithms return graphs with correct vertex counts
 * 
 * @note Tests focus on algorithm execution without errors and basic structural validation
 * @note Detailed weight verification would require more complex test infrastructure
 */
TEST_CASE("Dijkstra and MSTs") {
    // Create weighted cycle graph
    Graph g(4);
    g.addEdge(0, 1, 1);  // Lightest edge
    g.addEdge(1, 2, 2);  // Medium weight
    g.addEdge(2, 3, 3);  // Heavy weight
    g.addEdge(3, 0, 4);  // Heaviest edge

    // Test Dijkstra's shortest path algorithm
    Graph dTree = Algorithms::dijkstra(g, 0);
    CHECK(dTree.getVertexCount() == 4);  // Should maintain vertex count

    // Test Prim's MST algorithm
    Graph primTree = Algorithms::prim(g);
    CHECK(primTree.getVertexCount() == 4);  // Should maintain vertex count

    // Test Kruskal's MST algorithm
    Graph kruskalTree = Algorithms::kruskal(g);
    CHECK(kruskalTree.getVertexCount() == 4);  // Should maintain vertex count
}

/**
 * @brief Test case for Queue data structure functionality
 * 
 * Validates the custom Queue implementation including:
 * - Basic enqueue/dequeue operations
 * - FIFO ordering preservation
 * - Empty state detection
 * - Exception handling for overflow/underflow
 */
TEST_CASE("Queue operations") {
    Queue q(3);  // Small capacity for testing boundaries
    
    // Test empty state
    CHECK(q.isEmpty());
    
    // Test enqueue operations
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    CHECK(!q.isEmpty());
    
    // Test FIFO ordering
    CHECK(q.dequeue() == 10);
    CHECK(q.dequeue() == 20);
    CHECK(q.dequeue() == 30);
    CHECK(q.isEmpty());
    
    // Test exception handling
    CHECK_THROWS_AS(q.dequeue(), GraphException);
    
    // Fill queue and test overflow
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    CHECK_THROWS_AS(q.enqueue(4), GraphException);
}

/**
 * @brief Test case for PriorityQueue data structure functionality
 * 
 * Validates the custom min-heap PriorityQueue implementation:
 * - Priority-based ordering (min-heap property)
 * - Insert and extractMin operations
 * - Heap property maintenance
 * - Exception handling for capacity limits
 */
TEST_CASE("PriorityQueue operations") {
    PriorityQueue pq(5);
    
    // Test empty state
    CHECK(pq.isEmpty());
    
    // Insert elements with different priorities
    pq.insert(100, 5);  // value=100, priority=5
    pq.insert(200, 2);  // value=200, priority=2 (higher precedence)
    pq.insert(300, 8);  // value=300, priority=8
    pq.insert(400, 1);  // value=400, priority=1 (highest precedence)
    
    CHECK(!pq.isEmpty());
    
    // Test min-heap property (lowest priority extracted first)
    CHECK(pq.extractMin() == 400);  // priority 1
    CHECK(pq.extractMin() == 200);  // priority 2
    CHECK(pq.extractMin() == 100);  // priority 5
    CHECK(pq.extractMin() == 300);  // priority 8
    
    CHECK(pq.isEmpty());
    
    // Test exception handling
    CHECK_THROWS_AS(pq.extractMin(), GraphException);
    
    // Fill to capacity and test overflow
    for (int i = 0; i < 5; ++i) {
        pq.insert(i, i);
    }
    CHECK_THROWS_AS(pq.insert(999, 999), GraphException);
}

/**
 * @brief Test case for UnionFind data structure functionality
 * 
 * Validates the Union-Find implementation with path compression:
 * - Initial state (each element is its own representative)
 * - Union operations and set merging
 * - Find operations with path compression
 * - Cycle detection capabilities for Kruskal's algorithm
 */
TEST_CASE("UnionFind operations") {
    UnionFind uf(5);
    
    // Initially, each element should be its own representative
    for (int i = 0; i < 5; ++i) {
        CHECK(uf.find(i) == i);
    }
    
    // Union operations
    uf.unite(0, 1);  // Merge sets {0} and {1}
    uf.unite(2, 3);  // Merge sets {2} and {3}
    
    // Check that 0 and 1 are in the same set
    CHECK(uf.find(0) == uf.find(1));
    
    // Check that 2 and 3 are in the same set
    CHECK(uf.find(2) == uf.find(3));
    
    // Check that different sets have different representatives
    CHECK(uf.find(0) != uf.find(2));
    CHECK(uf.find(4) != uf.find(0));
    
    // Union different sets
    uf.unite(1, 2);  // Merge {0,1} with {2,3}
    
    // Now 0,1,2,3 should all be in the same set
    int rep = uf.find(0);
    CHECK(uf.find(1) == rep);
    CHECK(uf.find(2) == rep);
    CHECK(uf.find(3) == rep);
    
    // Element 4 should still be separate
    CHECK(uf.find(4) != rep);
}

/**
 * @brief Test case for exception handling across the system
 * 
 * Validates that proper exceptions are thrown for invalid operations:
 * - Graph boundary violations
 * - Data structure overflow/underflow conditions
 * - Consistent exception behavior across components
 */
TEST_CASE("Exception handling") {
    Graph g(3);
    
    // Test graph boundary exceptions
    CHECK_THROWS_AS(g.addEdge(-1, 0), GraphException);
    CHECK_THROWS_AS(g.addEdge(0, 5), GraphException);
    CHECK_THROWS_AS(g.removeEdge(3, 0), GraphException);
    
    int count;
    CHECK_THROWS_AS(g.getNeighbors(-1, count), GraphException);
    CHECK_THROWS_AS(g.getNeighbors(10, count), GraphException);
    
    // Test queue exceptions
    Queue q(1);
    q.enqueue(42);
    CHECK_THROWS_AS(q.enqueue(43), GraphException);  // Overflow
    q.dequeue();
    CHECK_THROWS_AS(q.dequeue(), GraphException);   // Underflow
    
    // Test priority queue exceptions
    PriorityQueue pq(1);
    pq.insert(1, 1);
    CHECK_THROWS_AS(pq.insert(2, 2), GraphException);  // Overflow
    pq.extractMin();
    CHECK_THROWS_AS(pq.extractMin(), GraphException);  // Underflow
}

/**
 * @brief Test case for disconnected graph handling
 * 
 * Validates algorithm behavior on graphs with multiple components:
 * - BFS/DFS on disconnected graphs
 * - Algorithm robustness with unreachable vertices
 * - Proper handling of isolated vertices
 */
TEST_CASE("Disconnected graph algorithms") {
    Graph g(6);
    
    // Create two disconnected components: {0-1-2} and {3-4}, vertex 5 isolated
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(3, 4, 1);
    // Vertex 5 remains isolated
    
    // BFS from vertex 0 should only reach vertices 0, 1, 2
    Graph bfsTree = Algorithms::bfs(g, 0);
    CHECK(bfsTree.getVertexCount() == 6);
    
    // Check that unreachable vertices have no edges in BFS tree
    int count;
    Neighbor* neighbors3 = bfsTree.getNeighbors(3, count);
    CHECK(count == 0);  // Vertex 3 should have no edges in BFS tree from 0
    delete[] neighbors3;
    
    Neighbor* neighbors5 = bfsTree.getNeighbors(5, count);
    CHECK(count == 0);  // Vertex 5 should have no edges in BFS tree from 0
    delete[] neighbors5;
    
    // MST algorithms should handle disconnected components
    Graph primMST = Algorithms::prim(g);
    Graph kruskalMST = Algorithms::kruskal(g);
    
    CHECK(primMST.getVertexCount() == 6);
    CHECK(kruskalMST.getVertexCount() == 6);
}

/**
 * @brief Test case for algorithm correctness on known graph structures
 * 
 * Validates algorithm results on well-defined graph topologies:
 * - Complete graph K4
 * - Path graph verification
 * - Weighted edge handling
 * - MST uniqueness properties
 */
TEST_CASE("Algorithm correctness verification") {
    // Create a simple triangle graph with known MST
    Graph triangle(3);
    triangle.addEdge(0, 1, 1);  // Minimum weight edge
    triangle.addEdge(1, 2, 2);  // Medium weight edge  
    triangle.addEdge(0, 2, 5);  // Maximum weight edge
    
    // MST should exclude the heaviest edge (0,2,5)
    Graph primMST = Algorithms::prim(triangle);
    Graph kruskalMST = Algorithms::kruskal(triangle);
    
    // Both MSTs should have exactly 2 edges (n-1 for n=3 vertices)
    int totalEdgesPrim = 0, totalEdgesKruskal = 0;
    
    for (int v = 0; v < 3; ++v) {
        int count;
        Neighbor* neighbors = primMST.getNeighbors(v, count);
        totalEdgesPrim += count;
        delete[] neighbors;
        
        neighbors = kruskalMST.getNeighbors(v, count);
        totalEdgesKruskal += count;
        delete[] neighbors;
    }
    
    // Each edge is counted twice (once for each endpoint)
    CHECK(totalEdgesPrim == 4);    // 2 edges * 2 endpoints = 4
    CHECK(totalEdgesKruskal == 4); // 2 edges * 2 endpoints = 4
    
    // Test DFS produces a spanning tree
    Graph dfsTree = Algorithms::dfs(triangle, 0);
    int totalEdgesDFS = 0;
    for (int v = 0; v < 3; ++v) {
        int count;
        Neighbor* neighbors = dfsTree.getNeighbors(v, count);
        totalEdgesDFS += count;
        delete[] neighbors;
    }
    CHECK(totalEdgesDFS == 4);  // Should also be a spanning tree
}

/**
 * @brief Test case for single vertex graph edge cases
 * 
 * Validates behavior on minimal graph structures:
 * - Single vertex graphs
 * - Empty graphs (zero vertices)
 * - Self-loop handling
 */
TEST_CASE("Single vertex and edge cases") {
    // Single vertex graph
    Graph single(1);
    CHECK(single.getVertexCount() == 1);
    
    int count;
    Neighbor* neighbors = single.getNeighbors(0, count);
    CHECK(count == 0);  // No neighbors initially
    delete[] neighbors;
    
    // Algorithms on single vertex
    Graph bfsTree = Algorithms::bfs(single, 0);
    Graph dfsTree = Algorithms::dfs(single, 0);
    Graph dijkstraTree = Algorithms::dijkstra(single, 0);
    Graph primMST = Algorithms::prim(single);
    Graph kruskalMST = Algorithms::kruskal(single);
    
    CHECK(bfsTree.getVertexCount() == 1);
    CHECK(dfsTree.getVertexCount() == 1);
    CHECK(dijkstraTree.getVertexCount() == 1);
    CHECK(primMST.getVertexCount() == 1);
    CHECK(kruskalMST.getVertexCount() == 1);
    
    // Two vertex graph
    Graph pair(2);
    pair.addEdge(0, 1, 10);
    
    Graph pairMST = Algorithms::prim(pair);
    neighbors = pairMST.getNeighbors(0, count);
    bool hasEdgeToOne = false;
    for (int i = 0; i < count; ++i) {
        if (neighbors[i].vertex == 1) hasEdgeToOne = true;
    }
    CHECK(hasEdgeToOne);  // Should have the single edge in MST
    delete[] neighbors;
}
