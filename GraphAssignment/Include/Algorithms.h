/** @author meirshuker159@gmail.com */


#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "Graph.h"
#include "GraphException.h"

namespace graph {

/**
 * @brief Static class containing various graph algorithms
 * 
 * This class provides implementations of classic graph algorithms without maintaining
 * any state. All methods are static and work on Graph objects passed as parameters.
 * The algorithms are implemented to work specifically with undirected weighted graphs
 * and return their results as new Graph objects representing trees or subgraphs.
 * 
 * @note All algorithms assume the input graph is connected for optimal results
 * @note The class uses custom data structures (Queue, PriorityQueue, UnionFind) instead of STL
 */
class Algorithms {
public:
    /**
     * @brief Perform Breadth-First Search starting from a given vertex
     * 
     * Performs BFS traversal on the graph starting from the specified vertex and
     * returns a spanning tree as a new Graph object. The resulting tree contains
     * only the edges that were traversed during the BFS, forming a shortest-path
     * tree in terms of number of edges.
     * 
     * @param g The input graph to traverse
     * @param start The starting vertex for BFS (0-based index)
     * @return Graph A new Graph object representing the BFS spanning tree
     * @throws GraphException if start vertex is invalid
     * 
     * @complexity Time: O(V + E), Space: O(V)
     * @note The returned graph has the same number of vertices as the input
     * @note Unreachable vertices will have no edges in the result tree
     */
    static Graph bfs(const Graph& g, int start);

    /**
     * @brief Perform Depth-First Search starting from a given vertex
     * 
     * Performs DFS traversal on the graph starting from the specified vertex and
     * returns a spanning tree (or forest) as a new Graph object. The resulting
     * tree contains only the tree edges discovered during DFS traversal.
     * 
     * @param g The input graph to traverse
     * @param start The starting vertex for DFS (0-based index)
     * @return Graph A new Graph object representing the DFS spanning tree/forest
     * @throws GraphException if start vertex is invalid
     * 
     * @complexity Time: O(V + E), Space: O(V)
     * @note The returned graph contains only tree edges, not back/forward/cross edges
     * @note If graph is disconnected, result may be a forest
     */
    static Graph dfs(const Graph& g, int start);

    /**
     * @brief Find shortest paths from a source vertex using Dijkstra's algorithm
     * 
     * Computes the shortest paths from the source vertex to all other vertices
     * using Dijkstra's algorithm. Returns a shortest-path tree as a new Graph object
     * where each edge represents the shortest path to that vertex.
     * 
     * @param g The input graph (must have non-negative edge weights)
     * @param start The source vertex (0-based index)
     * @return Graph A new Graph object representing the shortest-path tree
     * @throws GraphException if start vertex is invalid
     * @throws GraphException if graph contains negative edge weights
     * 
     * @complexity Time: O(V²), Space: O(V)
     * @note Assumes all edge weights are non-negative
     * @note Uses a custom priority queue implementation
     */
    static Graph dijkstra(const Graph& g, int start);

    /**
     * @brief Find Minimum Spanning Tree using Prim's algorithm
     * 
     * Computes the Minimum Spanning Tree (MST) of the graph using Prim's algorithm.
     * The algorithm starts from an arbitrary vertex and grows the MST by adding
     * the minimum weight edge that connects the current tree to a new vertex.
     * 
     * @param g The input connected graph
     * @return Graph A new Graph object representing the MST
     * @throws GraphException if graph is not connected
     * 
     * @complexity Time: O(V²), Space: O(V)
     * @note Assumes the input graph is connected
     * @note The resulting MST will have exactly V-1 edges for V vertices
     * @note Uses a custom priority queue implementation
     */
    static Graph prim(const Graph& g);

    /**
     * @brief Find Minimum Spanning Tree using Kruskal's algorithm
     * 
     * Computes the Minimum Spanning Tree (MST) of the graph using Kruskal's algorithm.
     * The algorithm sorts all edges by weight and adds them to the MST if they don't
     * create a cycle, using Union-Find data structure for cycle detection.
     * 
     * @param g The input connected graph
     * @return Graph A new Graph object representing the MST
     * @throws GraphException if graph is not connected
     * 
     * @complexity Time: O(E log E), Space: O(V)
     * @note Assumes the input graph is connected
     * @note The resulting MST will have exactly V-1 edges for V vertices
     * @note Uses custom Union-Find data structure for cycle detection
     */
    static Graph kruskal(const Graph& g);
};

} // namespace graph

#endif
