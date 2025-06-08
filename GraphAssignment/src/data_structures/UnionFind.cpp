/** @author meirshuker159@gmail.com */


#include "UnionFind.h"
#include "GraphException.h"

/**
 * @brief Constructor - Initialize Union-Find with specified number of elements
 * 
 * Creates parent and rank arrays, initializing each element as its own representative.
 * Each element starts as a singleton set with rank 0.
 * 
 * @details Initialization:
 * - parent[i] = i (each element is its own parent initially)  
 * - rank[i] = 0 (all trees start with rank 0)
 * 
 * @param s Number of elements in the universe (0-based indexing)
 */
UnionFind::UnionFind(int s) : size(s) {
    parent = new int[size];
    rank = new int[size];
    for (int i = 0; i < size; ++i) {
        parent[i] = i;  // Each element is initially its own parent
        rank[i] = 0;    // Initial rank is 0
    }
}

/**
 * @brief Destructor - Clean up allocated memory
 * 
 * Frees the dynamically allocated parent and rank arrays.
 */
UnionFind::~UnionFind() {
    delete[] parent;
    delete[] rank;
}

/**
 * @brief Find operation with path compression optimization
 * 
 * Finds the representative of the set containing element a.
 * Applies path compression by making every node on the path point directly
 * to the root, flattening the tree structure for future operations.
 * 
 * @details Path compression algorithm:
 * 1. If a is its own parent, return a (base case)
 * 2. Recursively find root and compress path: parent[a] = find(parent[a])
 * 3. Return the compressed path result
 * 
 * @param a Element whose set representative to find
 * @return Representative (root) of the set containing element a
 */
int UnionFind::find(int a) {
    if (parent[a] != a)
        parent[a] = find(parent[a]); // Path compression - flatten tree
    return parent[a];
}

/**
 * @brief Union operation with union by rank optimization
 * 
 * Merges the sets containing elements a and b by making the root of the
 * smaller rank tree point to the root of the larger rank tree.
 * This maintains balanced trees and prevents degeneration to linked lists.
 * 
 * @details Union by rank algorithm:
 * 1. Find representatives of both elements
 * 2. If same representative, already in same set - return
 * 3. Compare ranks and attach smaller rank tree under larger rank tree
 * 4. If ranks equal, pick one as new root and increment its rank
 * 
 * @param a First element to union
 * @param b Second element to union
 */
void UnionFind::unite(int a, int b) {
    int rootA = find(a);
    int rootB = find(b);
    
    if (rootA != rootB) {
        // Union by rank: attach smaller rank tree under root of larger rank tree
        if (rank[rootA] < rank[rootB]) {
            parent[rootA] = rootB;
        } else if (rank[rootA] > rank[rootB]) {
            parent[rootB] = rootA;
        } else {
            // Equal ranks: make rootA the new root and increment its rank
            parent[rootB] = rootA;
            rank[rootA]++;
        }
    }
}
