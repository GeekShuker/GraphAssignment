/** @author meirshuker159@gmail.com */


#ifndef GRAPH_EXCEPTION_H
#define GRAPH_EXCEPTION_H

namespace graph {

/**
 * @brief Simple custom exception class for all error conditions
 * 
 * A single exception class that can handle all error types in the graph
 * implementation, replacing std::overflow_error, std::underflow_error,
 * and std::out_of_range without any STL dependency.
 */
class GraphException {
public:
    /**
     * @brief Constructor with error message
     * @param msg Error message describing the exception
     */
    explicit GraphException(const char* msg) : message(msg) {}
    
    /**
     * @brief Get the error message
     * @return Pointer to the error message string
     */
    const char* what() const { return message; }
    
private:
    const char* message;
};

/**
 * @brief Custom swap function to replace std::swap
 * 
 * Simple template function to swap two values without STL dependency.
 * 
 * @tparam T Type of values to swap
 * @param a First value
 * @param b Second value
 */
template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

} // namespace graph

#endif 