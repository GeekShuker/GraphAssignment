/** @author meirshuker159@gmail.com */


#ifndef QUEUE_H
#define QUEUE_H

#include "../GraphException.h"

/**
 * @brief A basic FIFO queue implementation using a circular array
 * 
 * This class implements a queue data structure with fixed capacity using a circular
 * array approach. It provides standard queue operations (enqueue, dequeue, isEmpty)
 * and is specifically designed for use in graph traversal algorithms like BFS.
 * 
 * @note The queue has a fixed capacity set at construction time
 * @note Uses circular array implementation for efficient space utilization
 * @note No STL containers are used in this implementation
 */
class Queue {
public:
    /**
     * @brief Construct a new Queue object with specified capacity
     * 
     * Creates a queue with the given maximum capacity. The queue uses a circular
     * array internally to manage elements efficiently.
     * 
     * @param size The maximum number of elements the queue can hold
     * @throws GraphException if size <= 0
     * 
     * @complexity Time: O(1), Space: O(size)
     */
    Queue(int size);

    /**
     * @brief Destroy the Queue object and free allocated memory
     * 
     * Cleans up all dynamically allocated memory used by the queue.
     */
    ~Queue();

    /**
     * @brief Add an element to the rear of the queue
     * 
     * Inserts a new element at the rear of the queue following FIFO order.
     * 
     * @param value The integer value to add to the queue
     * @throws GraphException if the queue is full
     * 
     * @complexity Time: O(1), Space: O(1)
     */
    void enqueue(int value);

    /**
     * @brief Remove and return the front element of the queue
     * 
     * Removes the element at the front of the queue and returns its value.
     * 
     * @return int The value of the front element
     * @throws GraphException if the queue is empty
     * 
     * @complexity Time: O(1), Space: O(1)
     */
    int dequeue();

    /**
     * @brief Check if the queue is empty
     * 
     * @return true if the queue contains no elements
     * @return false if the queue contains at least one element
     * 
     * @complexity Time: O(1), Space: O(1)
     */
    bool isEmpty() const;

private:
    int* data;      ///< Dynamic array to store queue elements
    int front;      ///< Index of the front element
    int rear;       ///< Index of the rear element
    int capacity;   ///< Maximum capacity of the queue
    int count;      ///< Current number of elements in the queue
};

#endif
