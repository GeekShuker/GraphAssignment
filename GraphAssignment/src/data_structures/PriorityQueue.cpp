/** @author meirshuker159@gmail.com */

#include "PriorityQueue.h"
#include "GraphException.h"

/**
 * @brief Constructor - Initialize priority queue with specified capacity
 *
 * Creates a min-heap based priority queue with the given capacity.
 * Validates input and initializes the heap array and sets size to 0.
 *
 * @param cap Maximum capacity of the priority queue
 * @throws GraphException if cap <= 0
 */
PriorityQueue::PriorityQueue(int cap) : capacity(cap), size(0) {
    if (cap <= 0)
        throw graph::GraphException("Priority Queue capacity must be positive");
    heap = new Element[capacity];
}

/**
 * @brief Destructor - Clean up allocated memory
 *
 * Frees the dynamically allocated heap array.
 * Automatically called when priority queue object goes out of scope.
 */
PriorityQueue::~PriorityQueue() {
    delete[] heap;
}

/**
 * @brief Insert an element with its priority into the queue
 *
 * Adds a new element to the priority queue with the specified priority.
 * The element is positioned according to min-heap property using heapifyUp.
 *
 * @details Implementation steps:
 * 1. Check if queue is full
 * 2. Add element at end of heap array
 * 3. Call heapifyUp to maintain min-heap property
 * 4. Increment size
 *
 * @param value The value to be inserted
 * @param priority Priority of the element (lower = higher precedence)
 * @throws GraphException if the priority queue is at maximum capacity
 */
void PriorityQueue::insert(int value, int priority) {
    if (size == capacity)
        throw graph::GraphException("Priority Queue is full");

    heap[size] = {value, priority};
    heapifyUp(size);
    size++;
}

/**
 * @brief Extract and return the element with minimum priority
 *
 * Removes and returns the element with the lowest priority value.
 * Maintains min-heap property by moving last element to root and heapifying down.
 *
 * @details Implementation steps:
 * 1. Check if queue is empty
 * 2. Save the minimum value (at root)
 * 3. Move last element to root position
 * 4. Decrement size
 * 5. Call heapifyDown to restore min-heap property
 * 6. Return the saved minimum value
 *
 * @return The value of the element with minimum priority
 * @throws GraphException if the priority queue is empty
 */
int PriorityQueue::extractMin() {
    if (isEmpty())
        throw graph::GraphException("Priority Queue is empty");

    int minValue = heap[0].value;
    heap[0] = heap[--size];  // Move last element to root and decrement size
    heapifyDown(0);          // Restore heap property
    return minValue;
}

/**
 * @brief Check if the priority queue is empty
 *
 * @return true if the priority queue contains no elements, false otherwise
 */
bool PriorityQueue::isEmpty() const {
    return size == 0;
}

/**
 * @brief Restore min-heap property by moving element up the tree
 *
 * Helper function that moves an element up the heap tree until the
 * min-heap property is satisfied. Used after insertion.
 *
 * @details Algorithm:
 * - Compare element with its parent
 * - If element has lower priority than parent, swap them
 * - Continue until root is reached or heap property is satisfied
 *
 * @param i Index of the element to heapify up
 */
void PriorityQueue::heapifyUp(int i) {
    while (i > 0 && heap[i].priority < heap[(i - 1) / 2].priority) {
        graph::swap(heap[i], heap[(i - 1) / 2]);
        i = (i - 1) / 2;  // Move to parent index
    }
}

/**
 * @brief Restore min-heap property by moving element down the tree
 *
 * Helper function that moves an element down the heap tree until the
 * min-heap property is satisfied. Used after extraction.
 *
 * @details Algorithm:
 * - Find the child with minimum priority
 * - If current element has higher priority than minimum child, swap them
 * - Continue recursively until heap property is satisfied
 *
 * @param i Index of the element to heapify down
 */
void PriorityQueue::heapifyDown(int i) {
    int left = 2 * i + 1;    // Left child index
    int right = 2 * i + 2;   // Right child index
    int smallest = i;        // Index of element with smallest priority

    // Find child with minimum priority
    if (left < size && heap[left].priority < heap[smallest].priority)
        smallest = left;
    if (right < size && heap[right].priority < heap[smallest].priority)
        smallest = right;

    // If current element is not the smallest, swap and continue
    if (smallest != i) {
        graph::swap(heap[i], heap[smallest]);
        heapifyDown(smallest);  // Recursive call
    }
}
