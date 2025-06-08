/** @author meirshuker159@gmail.com */


#ifndef GRAPH_H
#define GRAPH_H

#include "GraphException.h"

namespace graph {

/**
 * @brief Structure to represent a neighbor vertex with its weight
 * 
 * This structure is used to return neighbor information from the graph
 * without exposing the internal linked list implementation.
 */
struct Neighbor {
    int vertex;  ///< The neighbor vertex ID
    int weight;  ///< The weight of the edge to this neighbor
};

/**
 * @brief Graph class implementing an undirected weighted graph using adjacency lists
 * 
 * This class provides a complete implementation of an undirected weighted graph
 * using adjacency lists for efficient storage and traversal. The number of vertices
 * is fixed at construction time and cannot be changed afterward.
 * 
 * @note The graph uses 0-based vertex indexing
 * @note All edges are undirected (bidirectional)
 * @note STL containers are not used in this implementation
 */
class Graph {
public:
    /**
     * @brief Construct a new Graph object with a fixed number of vertices
     * 
     * @param vertices The number of vertices in the graph (must be > 0)
     * @throws GraphException if vertices <= 0
     */
    Graph(int vertices);

    /**
     * @brief Destroy the Graph object and free all allocated memory
     * 
     * This destructor ensures proper cleanup of all dynamically allocated
     * memory including the adjacency list and all node structures.
     */
    ~Graph();

    /**
     * @brief Add an undirected edge between two vertices
     * 
     * Adds an edge between source and destination vertices with the specified weight.
     * Since the graph is undirected, the edge is added in both directions.
     * 
     * @param src Source vertex (0-based index)
     * @param dest Destination vertex (0-based index)  
     * @param weight Weight of the edge (default: 1)
     * @throws GraphException if src or dest are invalid vertex indices
     */
    void addEdge(int src, int dest, int weight = 1);

    /**
     * @brief Remove an undirected edge between two vertices
     * 
     * Removes the edge between source and destination vertices.
     * Since the graph is undirected, the edge is removed from both directions.
     * 
     * @param src Source vertex (0-based index)
     * @param dest Destination vertex (0-based index)
     * @throws GraphException if src or dest are invalid vertex indices
     * @throws GraphException if the edge does not exist
     */
    void removeEdge(int src, int dest);

    /**
     * @brief Print the graph's adjacency list representation
     * 
     * Outputs the graph in a human-readable format showing each vertex
     * and its neighbors with their corresponding edge weights.
     */
    void print_graph() const;

    /**
     * @brief Get the number of vertices in the graph
     * 
     * @return int The total number of vertices
     */
    int getVertexCount() const;

    /**
     * @brief Get all neighbors of a specific vertex
     * 
     * Returns an array of Neighbor structures containing all adjacent vertices
     * and their edge weights. The caller is responsible for deleting the returned array.
     * 
     * @param vertex The vertex whose neighbors to retrieve (0-based index)
     * @param count Reference to store the number of neighbors found
     * @return Neighbor* Dynamically allocated array of neighbors (must be deleted by caller)
     * @throws GraphException if vertex is an invalid index
     * 
     * @note The returned array must be freed using delete[] by the caller
     */
    Neighbor* getNeighbors(int vertex, int& count) const;

private:
    /**
     * @brief Internal node structure for the adjacency list
     * 
     * Each node represents an edge in the adjacency list, containing
     * the destination vertex, edge weight, and pointer to the next node.
     */
    struct Node {
        int vertex;   ///< Destination vertex
        int weight;   ///< Edge weight
        Node* next;   ///< Pointer to next node in the list
    };

    int numVertices;        ///< Total number of vertices in the graph
    Node** adjacencyList;   ///< Array of pointers to adjacency lists

    /**
     * @brief Create a new node for the adjacency list
     * 
     * @param vertex The vertex this node points to
     * @param weight The weight of the edge
     * @return Node* Pointer to the newly created node
     */
    Node* createNode(int vertex, int weight);

    /**
     * @brief Delete a linked list starting from the given head
     * 
     * @param head Pointer to the head of the list to delete
     */
    void deleteList(Node* head);
};

} // namespace graph

#endif
