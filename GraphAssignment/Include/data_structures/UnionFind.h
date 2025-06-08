/** @author meirshuker159@gmail.com */


#ifndef UNION_FIND_H
#define UNION_FIND_H

#include "../GraphException.h"

/**
 * @brief Union-Find (Disjoint Set Union) data structure implementation
 * 
 * This class implements the Union-Find data structure with two key optimizations:
 * path compression in the find operation and union by rank for balanced trees.
 * It efficiently supports operations to determine if two elements are in the same
 * set and to merge two sets, making it ideal for Kruskal's MST algorithm.
 * 
 * @note Uses path compression for nearly constant amortized find operations
 * @note Uses union by rank to maintain balanced trees and prevent degeneration
 * @note No STL containers are used in this implementation
 */
class UnionFind {
public:
    /**
     * @brief Construct a new Union-Find object with specified number of elements
     * 
     * Initializes the Union-Find data structure with the given number of elements.
     * Initially, each element forms its own singleton set.
     * 
     * @param size The number of elements in the universe (0 to size-1)
     * @throws GraphException if size <= 0
     * 
     * @complexity Time: O(n), Space: O(n)
     */
    UnionFind(int size);

    /**
     * @brief Destroy the Union-Find object and free allocated memory
     * 
     * Cleans up all dynamically allocated memory used by the parent and rank arrays.
     */
    ~UnionFind();

    /**
     * @brief Find the representative (root) of the set containing element a
     * 
     * Finds and returns the representative of the set containing element a.
     * Uses path compression optimization to flatten the tree structure for
     * future operations, achieving nearly constant amortized time complexity.
     * 
     * @param a The element whose set representative to find (0-based index)
     * @return int The representative of the set containing element a
     * @throws GraphException if a is not a valid element index
     * 
     * @complexity Amortized time: O(α(n)), Space: O(1)
     * @note α(n) is the inverse Ackermann function, practically constant
     */
    int find(int a);

    /**
     * @brief Union the sets containing elements a and b
     * 
     * Merges the sets containing elements a and b into a single set.
     * Uses union by rank optimization to maintain balanced trees by making
     * the root of the smaller rank tree point to the root of the larger rank tree.
     * 
     * @param a First element (0-based index)
     * @param b Second element (0-based index)
     * @throws GraphException if a or b are not valid element indices
     * 
     * @complexity Amortized time: O(α(n)), Space: O(1)
     * @note If a and b are already in the same set, no operation is performed
     * @note α(n) is the inverse Ackermann function, practically constant
     */
    void unite(int a, int b);

private:
    int* parent;    ///< Parent array: parent[i] is the parent of element i
    int* rank;      ///< Rank array: rank[i] is the rank (depth bound) of tree rooted at i
    int size;       ///< Total number of elements in the universe
};

#endif
