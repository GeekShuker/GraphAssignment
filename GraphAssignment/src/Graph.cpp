/** @author meirshuker159@gmail.com */


#include "Graph.h"
#include <iostream>
#include "GraphException.h"

namespace graph {

/**
 * @brief Constructor - Initialize graph with specified number of vertices
 * 
 * Creates a new graph with the given number of vertices. Initializes the
 * adjacency list array where each element points to the head of a linked
 * list containing the neighbors of that vertex.
 * 
 * @details The implementation allocates an array of Node pointers, one for
 * each vertex. Each pointer is initialized to nullptr indicating no edges
 * initially exist.
 */
Graph::Graph(int vertices) : numVertices(vertices) {
    adjacencyList = new Node*[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        adjacencyList[i] = nullptr;
    }
}

/**
 * @brief Destructor - Clean up all allocated memory
 * 
 * Destroys the graph by first deleting all linked lists (one for each vertex)
 * and then deleting the main adjacency list array. This ensures no memory leaks.
 * 
 * @details For each vertex, deleteList() is called to free the entire linked
 * list of neighbors. Finally, the array of pointers itself is deleted.
 */
Graph::~Graph() {
    for (int i = 0; i < numVertices; ++i) {
        deleteList(adjacencyList[i]);
    }
    delete[] adjacencyList;
}

/**
 * @brief Create a new node for the adjacency list
 * 
 * Helper function to create and initialize a new Node structure with the
 * given vertex and weight values. The next pointer is set to nullptr.
 * 
 * @details This function encapsulates node creation to ensure consistent
 * initialization and makes the code more maintainable.
 * 
 * @param vertex The destination vertex this node represents
 * @param weight The weight of the edge to this vertex
 * @return Pointer to the newly created and initialized node
 */
Graph::Node* Graph::createNode(int vertex, int weight) {
    Node* newNode = new Node;
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = nullptr;
    return newNode;
}

/**
 * @brief Delete an entire linked list starting from the given head
 * 
 * Helper function to recursively delete all nodes in a linked list.
 * Used during destruction and edge removal operations.
 * 
 * @details Iterates through the linked list, deleting each node while
 * advancing to the next node. This prevents memory leaks when removing
 * adjacency lists.
 * 
 * @param head Pointer to the head of the list to delete
 */
void Graph::deleteList(Node* head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

/**
 * @brief Add an undirected edge between two vertices
 * 
 * Adds an edge with the specified weight between source and destination
 * vertices. Since the graph is undirected, the edge is added in both
 * directions by inserting nodes at the heads of both adjacency lists.
 * 
 * @details The implementation uses head insertion for O(1) complexity.
 * First validates vertex indices, then creates two nodes (one for each
 * direction) and inserts them at the heads of the respective adjacency lists.
 * 
 * @param src Source vertex index (0-based)
 * @param dest Destination vertex index (0-based)  
 * @param weight Weight of the edge (default: 1)
 * @throws std::out_of_range if vertex indices are invalid
 */
void Graph::addEdge(int src, int dest, int weight) {
    if (src < 0 || src >= numVertices || dest < 0 || dest >= numVertices) 
        throw GraphException("Vertex index out of bounds");

    // Add edge from src to dest
    Node* newNode = createNode(dest, weight);
    newNode->next = adjacencyList[src];
    adjacencyList[src] = newNode;

    // Add edge from dest to src (undirected graph)
    newNode = createNode(src, weight);
    newNode->next = adjacencyList[dest];
    adjacencyList[dest] = newNode;
}

/**
 * @brief Remove an undirected edge between two vertices
 * 
 * Removes the edge between source and destination vertices by searching
 * and deleting the corresponding nodes from both adjacency lists.
 * 
 * @details The implementation uses pointer-to-pointer technique for efficient
 * node removal without special handling for head node. Searches both adjacency
 * lists and removes the first occurrence of each edge direction.
 * 
 * @param src Source vertex index (0-based)
 * @param dest Destination vertex index (0-based)
 * @throws std::out_of_range if vertex indices are invalid
 * 
 * @note If the edge doesn't exist, the operation completes without error
 */
void Graph::removeEdge(int src, int dest) {
    if (src < 0 || src >= numVertices || dest < 0 || dest >= numVertices) 
        throw GraphException("Vertex index out of bounds");

    // Remove edge from src to dest
    Node** current = &adjacencyList[src];
    while (*current) {
        if ((*current)->vertex == dest) {
            Node* temp = *current;
            *current = (*current)->next;
            delete temp;
            break;
        }
        current = &((*current)->next);
    }

    // Remove edge from dest to src (undirected graph)
    current = &adjacencyList[dest];
    while (*current) {
        if ((*current)->vertex == src) {
            Node* temp = *current;
            *current = (*current)->next;
            delete temp;
            break;
        }
        current = &((*current)->next);
    }
}

/**
 * @brief Print the graph's adjacency list representation
 * 
 * Outputs the graph in a human-readable format showing each vertex
 * followed by its list of neighbors with their edge weights.
 * 
 * @details Iterates through each vertex and its adjacency list, printing
 * the vertex number followed by all its neighbors in the format:
 * "Vertex X: -> (neighbor, weight: W) -> (neighbor, weight: W) ..."
 */
void Graph::print_graph() const {
    for (int i = 0; i < numVertices; ++i) {
        std::cout << "Vertex " << i << ":";
        Node* temp = adjacencyList[i];
        while (temp) {
            std::cout << " -> (" << temp->vertex << ", weight: " << temp->weight << ")";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
}

/**
 * @brief Get the total number of vertices in the graph
 * 
 * Simple getter method that returns the number of vertices that was
 * set during graph construction.
 * 
 * @return The total number of vertices in the graph
 */
int Graph::getVertexCount() const {
    return numVertices;
}

/**
 * @brief Get all neighbors of a specific vertex as an array
 * 
 * Returns a dynamically allocated array of Neighbor structures containing
 * all adjacent vertices and their edge weights. The caller must delete the
 * returned array to prevent memory leaks.
 * 
 * @details The implementation makes two passes: first to count neighbors,
 * then to populate the array. This approach avoids using dynamic containers
 * while providing a clean interface to the caller.
 * 
 * @param vertex The vertex whose neighbors to retrieve (0-based index)
 * @param count Reference parameter to store the number of neighbors found
 * @return Dynamically allocated array of Neighbor structures
 * @throws std::out_of_range if vertex index is invalid
 * 
 * @warning The caller is responsible for deleting the returned array using delete[]
 */
Neighbor* Graph::getNeighbors(int vertex, int& count) const {
    if (vertex < 0 || vertex >= numVertices) 
        throw GraphException("Vertex index out of bounds");

    count = 0;
    Node* temp = adjacencyList[vertex];

    // First pass: count neighbors
    while (temp) {
        count++;
        temp = temp->next;
    }

    // Allocate array and populate with neighbor data
    Neighbor* neighbors = new Neighbor[count];
    temp = adjacencyList[vertex];
    int i = 0;
    while (temp) {
        neighbors[i].vertex = temp->vertex;
        neighbors[i].weight = temp->weight;
        temp = temp->next;
        ++i;
    }

    return neighbors;
}

} // namespace graph
