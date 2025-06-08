/** @author meirshuker159@gmail.com */


#include "Graph.h"
#include "Algorithms.h"
#include "data_structures/Queue.h"
#include "data_structures/PriorityQueue.h"
#include "data_structures/UnionFind.h"
#include "GraphException.h"
#include <iostream>
#include <climits>
//s
namespace graph {

// BFS: Breadth-First Search returning a BFS tree rooted at 'start'
Graph Algorithms::bfs(const Graph& g, int start) {
    int n = g.getVertexCount();
    Graph tree(n);
    bool* visited = new bool[n]();
    Queue q(n);

    visited[start] = true;
    q.enqueue(start);

    while (!q.isEmpty()) {
        int u = q.dequeue();
        int count;
        Neighbor* neighbors = g.getNeighbors(u, count);
        for (int i = 0; i < count; ++i) {
            int v = neighbors[i].vertex;
            int w = neighbors[i].weight;
            if (!visited[v]) {
                visited[v] = true;
                tree.addEdge(u, v, w);
                q.enqueue(v);
            }
        }
        delete[] neighbors;
    }
    delete[] visited;
    return tree;
}

// DFS helper
void dfs_visit(const Graph& g, int u, bool* visited, Graph& tree) {
    visited[u] = true;
    int count;
    Neighbor* neighbors = g.getNeighbors(u, count);
    for (int i = 0; i < count; ++i) {
        int v = neighbors[i].vertex;
        int w = neighbors[i].weight;
        if (!visited[v]) {
            tree.addEdge(u, v, w);
            dfs_visit(g, v, visited, tree);
        }
    }
    delete[] neighbors;
}

Graph Algorithms::dfs(const Graph& g, int start) {
    int n = g.getVertexCount();
    Graph tree(n);
    bool* visited = new bool[n]();
    dfs_visit(g, start, visited, tree);
    delete[] visited;
    return tree;
}

// Dijkstra: Shortest path tree from 'start' using weights
Graph Algorithms::dijkstra(const Graph& g, int start) {
    int n = g.getVertexCount();
    Graph tree(n);
    int* dist = new int[n];
    int* prev = new int[n];
    for (int i = 0; i < n; ++i) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }
    dist[start] = 0;

    PriorityQueue pq(n);
    pq.insert(start, 0);

    while (!pq.isEmpty()) {
        int u = pq.extractMin();
        int count;
        Neighbor* neighbors = g.getNeighbors(u, count);
        for (int i = 0; i < count; ++i) {
            int v = neighbors[i].vertex;
            int w = neighbors[i].weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.insert(v, dist[v]);
            }
        }
        delete[] neighbors;
    }

    for (int v = 0; v < n; ++v) {
        if (prev[v] != -1)
            tree.addEdge(prev[v], v, dist[v] - dist[prev[v]]);
    }
    delete[] dist;
    delete[] prev;
    return tree;
}

// Prim: Minimum spanning tree using priority queue
Graph Algorithms::prim(const Graph& g) {
    int n = g.getVertexCount();
    Graph tree(n);
    bool* inMST = new bool[n]();
    int* key = new int[n];
    int* parent = new int[n];
    for (int i = 0; i < n; ++i) {
        key[i] = INT_MAX;
        parent[i] = -1;
    }
    key[0] = 0;

    PriorityQueue pq(n);
    pq.insert(0, 0);

    while (!pq.isEmpty()) {
        int u = pq.extractMin();
        inMST[u] = true;

        int count;
        Neighbor* neighbors = g.getNeighbors(u, count);
        for (int i = 0; i < count; ++i) {
            int v = neighbors[i].vertex;
            int w = neighbors[i].weight;
            if (!inMST[v] && w < key[v]) {
                key[v] = w;
                parent[v] = u;
                pq.insert(v, key[v]);
            }
        }
        delete[] neighbors;
    }

    for (int v = 1; v < n; ++v) {
        if (parent[v] != -1)
            tree.addEdge(parent[v], v, key[v]);
    }
    delete[] inMST;
    delete[] key;
    delete[] parent;
    return tree;
}

// Kruskal: Minimum spanning tree using union-find
Graph Algorithms::kruskal(const Graph& g) {
    int n = g.getVertexCount();
    Graph tree(n);
    UnionFind uf(n);

    // Collect all edges manually (no STL vector)
    struct Edge {
        int w, u, v;
    } edges[500]; // assuming at most 500 edges
    int edgeCount = 0;

    for (int u = 0; u < n; ++u) {
        int count;
        Neighbor* neighbors = g.getNeighbors(u, count);
        for (int i = 0; i < count; ++i) {
            int v = neighbors[i].vertex;
            int w = neighbors[i].weight;
            if (u < v) {
                edges[edgeCount++] = {w, u, v};
            }
        }
        delete[] neighbors;
    }

    // Bubble sort edges by weight
    for (int i = 0; i < edgeCount; ++i) {
        for (int j = i + 1; j < edgeCount; ++j) {
            if (edges[j].w < edges[i].w) {
                Edge temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
        }
    }

    for (int i = 0; i < edgeCount; ++i) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        if (uf.find(u) != uf.find(v)) {
            tree.addEdge(u, v, w);
            uf.unite(u, v);
        }
    }

    return tree;
}

} // namespace graph
