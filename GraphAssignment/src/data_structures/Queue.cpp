/** @author meirshuker159@gmail.com */


#include "Queue.h"
#include "GraphException.h"

/**
 * @brief Constructor - Initialize queue with specified capacity
 * 
 * Creates a circular array-based queue with the given capacity.
 * Initializes all pointers and counters to represent an empty queue.
 * 
 * @details The implementation uses:
 * - front: index of the first element
 * - rear: index of the last element  
 * - count: number of elements currently in queue
 * - capacity: maximum number of elements
 * 
 * @param size Maximum capacity of the queue
 */
Queue::Queue(int size) : front(0), rear(-1), capacity(size), count(0) {
    data = new int[capacity];
}

/**
 * @brief Destructor - Clean up allocated memory
 * 
 * Frees the dynamically allocated array used to store queue elements.
 * Automatically called when queue object goes out of scope.
 */
Queue::~Queue() {
    delete[] data;
}

/**
 * @brief Add an element to the rear of the queue
 * 
 * Inserts a new element at the rear of the queue using circular array logic.
 * The rear pointer wraps around to the beginning when it reaches capacity.
 * 
 * @details Implementation steps:
 * 1. Check if queue is full (count == capacity)
 * 2. Advance rear pointer in circular fashion: (rear + 1) % capacity
 * 3. Store value at new rear position
 * 4. Increment count
 * 
 * @param value The integer value to add to the queue
 * @throws std::overflow_error if the queue is at maximum capacity
 * 
 * @complexity Time: O(1), Space: O(1)
 */
void Queue::enqueue(int value) {
    if (count == capacity) 
        throw graph::GraphException("Queue is full");
    
    rear = (rear + 1) % capacity;  // Circular increment
    data[rear] = value;
    count++;
}

/**
 * @brief Remove and return the front element of the queue
 * 
 * Removes the element at the front of the queue and returns its value.
 * The front pointer advances in circular fashion to maintain queue order.
 * 
 * @details Implementation steps:
 * 1. Check if queue is empty
 * 2. Get value at front position
 * 3. Advance front pointer: (front + 1) % capacity
 * 4. Decrement count
 * 5. Return the retrieved value
 * 
 * @return The value of the front element
 * @throws std::underflow_error if the queue is empty
 * 
 * @complexity Time: O(1), Space: O(1)
 */
int Queue::dequeue() {
    if (isEmpty()) 
        throw graph::GraphException("Queue is empty");
    
    int value = data[front];
    front = (front + 1) % capacity;  // Circular increment
    count--;
    return value;
}

/**
 * @brief Check if the queue is empty
 * 
 * Determines whether the queue contains any elements by checking the count.
 * 
 * @return true if the queue contains no elements, false otherwise
 * 
 * @complexity Time: O(1), Space: O(1)
 */
bool Queue::isEmpty() const {
    return count == 0;
}
