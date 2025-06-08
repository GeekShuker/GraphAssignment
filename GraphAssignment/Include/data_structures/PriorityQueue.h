/** @author meirshuker159@gmail.com */

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "../GraphException.h"

/**
 * @brief A min-heap based priority queue implementation
 * 
 * This class implements a priority queue using a binary min-heap data structure.
 * Elements are stored with associated priorities, and the element with the lowest
 * priority value can be efficiently extracted. This implementation is specifically
 * designed for graph algorithms like Dijkstra's shortest path and Prim's MST.
 * 
 * @note The priority queue uses a min-heap (lowest priority = highest precedence)
 * @note Fixed capacity set at construction time
 * @note No STL containers are used in this implementation
 */
class PriorityQueue {
public:
    /**
     * @brief Construct a new Priority Queue object with specified capacity
     * 
     * Creates a priority queue with the given maximum capacity using a min-heap
     * implementation.
     * 
     * @param size The maximum number of elements the priority queue can hold
     * @throws GraphException if size <= 0
     * 
     * @complexity Time: O(1), Space: O(size)
     */
    PriorityQueue(int size);

    /**
     * @brief Destroy the Priority Queue object and free allocated memory
     * 
     * Cleans up all dynamically allocated memory used by the priority queue.
     */
    ~PriorityQueue();

    /**
     * @brief Insert an element with its priority into the queue
     * 
     * Adds a new element to the priority queue with the specified priority value.
     * The element is positioned in the heap according to its priority (min-heap property).
     * 
     * @param value The value to be inserted
     * @param priority The priority of the element (lower values = higher precedence)
     * @throws GraphException if the priority queue is full
     * 
     * @complexity Time: O(log n), Space: O(1)
     * @note Lower priority values have higher precedence (min-heap)
     */
    void insert(int value, int priority);

    /**
     * @brief Extract and return the element with minimum priority
     * 
     * Removes and returns the element with the lowest priority value from the queue.
     * The heap property is maintained after removal.
     * 
     * @return int The value of the element with minimum priority
     * @throws GraphException if the priority queue is empty
     * 
     * @complexity Time: O(log n), Space: O(1)
     */
    int extractMin();

    /**
     * @brief Check if the priority queue is empty
     * 
     * @return true if the priority queue contains no elements
     * @return false if the priority queue contains at least one element
     * 
     * @complexity Time: O(1), Space: O(1)
     */
    bool isEmpty() const;

private:
    /**
     * @brief Structure to represent an element with its priority
     * 
     * Each element in the priority queue consists of a value and its
     * associated priority for comparison in the min-heap.
     */
    struct Element {
        int value;      ///< The actual data value
        int priority;   ///< Priority of the element (lower = higher precedence)
    };

    Element* heap;   ///< Dynamic array representing the min-heap
    int capacity;    ///< Maximum capacity of the priority queue
    int size;        ///< Current number of elements in the queue

    /**
     * @brief Restore min-heap property by moving element up the tree
     * 
     * Helper method to maintain min-heap property after insertion.
     * Moves element up until heap property is satisfied.
     * 
     * @param i Index of element to heapify up
     */
    void heapifyUp(int i);

    /**
     * @brief Restore min-heap property by moving element down the tree
     * 
     * Helper method to maintain min-heap property after extraction.
     * Moves element down until heap property is satisfied.
     * 
     * @param i Index of element to heapify down
     */
    void heapifyDown(int i);
};

#endif
