/** @author meirshuker159@gmail.com */

#include "Include/Graph.h"
#include "Include/Algorithms.h"
#include <iostream>

using namespace graph;

/**
 * @brief Main demonstration function
 * 
 * Creates a sample weighted graph and demonstrates all implemented algorithms.
 * The graph structure is designed to showcase different algorithm behaviors:
 * 
 * Graph topology:
 * - 5 vertices (0-4)
 * - Weighted edges forming a connected graph
 * - Multiple paths between vertices to demonstrate shortest path algorithms
 * - Different edge weights to show MST algorithm behavior
 * 
 * @details Demonstration sequence:
 * 1. Create graph with 5 vertices
 * 2. Add weighted edges: (0,1,4), (0,2,1), (1,2,2), (1,3,5), (2,3,8), (3,4,3)
 * 3. Display original graph structure
 * 4. Run and display BFS tree starting from vertex 0
 * 5. Run and display DFS tree starting from vertex 0
 * 6. Run and display Dijkstra shortest path tree from vertex 0
 * 7. Run and display Prim's MST
 * 8. Run and display Kruskal's MST
 * 
 * @return 0 on successful completion
 * 
 * @note All algorithms return new Graph objects representing their results
 * @note Output format shows each vertex followed by its neighbors and edge weights
 */
int main() {
    std::cout << "=== Graph Algorithms Demonstration ===" << std::endl;
    std::cout << "Creating a sample weighted graph with 5 vertices...\n" << std::endl;
    
    // Create a graph with 5 vertices (0, 1, 2, 3, 4)
    Graph g(5);

    // Add weighted edges to create a connected graph
    // Edge weights chosen to demonstrate algorithm differences
    g.addEdge(0, 1, 4);  // Medium weight edge
    g.addEdge(0, 2, 1);  // Lightest edge from vertex 0
    g.addEdge(1, 2, 2);  // Creates shorter path from 0 to 2
    g.addEdge(1, 3, 5);  // Heavy edge to vertex 3
    g.addEdge(2, 3, 8);  // Heaviest edge in graph
    g.addEdge(3, 4, 3);  // Connection to isolated vertex 4

    // Display the original graph structure
    std::cout << "Original Graph:" << std::endl;
    std::cout << "(Format: Vertex X: -> (neighbor, weight: W))" << std::endl;
    g.print_graph();

    // Demonstrate BFS - shows shortest path tree in terms of edge count
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "BFS Tree (starting from vertex 0):" << std::endl;
    std::cout << "Shows shortest paths by number of edges" << std::endl;
    Graph bfsTree = Algorithms::bfs(g, 0);
    bfsTree.print_graph();

    // Demonstrate DFS - shows one possible spanning tree via depth-first exploration
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "DFS Tree (starting from vertex 0):" << std::endl;
    std::cout << "Shows spanning tree from depth-first traversal" << std::endl;
    Graph dfsTree = Algorithms::dfs(g, 0);
    dfsTree.print_graph();

    // Demonstrate Dijkstra - shows shortest path tree by edge weights
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "Dijkstra Tree (starting from vertex 0):" << std::endl;
    std::cout << "Shows shortest paths by total edge weight" << std::endl;
    Graph dijkstraTree = Algorithms::dijkstra(g, 0);
    dijkstraTree.print_graph();

    // Demonstrate Prim's MST - grows tree by adding minimum weight edges
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "Prim MST:" << std::endl;
    std::cout << "Minimum spanning tree using Prim's algorithm" << std::endl;
    Graph primTree = Algorithms::prim(g);
    primTree.print_graph();

    // Demonstrate Kruskal's MST - sorts edges and adds if no cycle
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "Kruskal MST:" << std::endl;
    std::cout << "Minimum spanning tree using Kruskal's algorithm" << std::endl;
    Graph kruskalTree = Algorithms::kruskal(g);
    kruskalTree.print_graph();

    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "Demonstration completed successfully!" << std::endl;
    std::cout << "All algorithms executed without errors." << std::endl;

    return 0;
}
