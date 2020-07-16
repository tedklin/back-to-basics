#pragma once

#include "bfs.hpp"
#include "graph.hpp"

#include <stack>

namespace graphlib {

enum class EdgeType { TREE, BACK, FORWARD, CROSS, UNCLASSIFIED };

// Traditional DFS algorithm.
void dfs(Graph* graph, const Vertex* search_root,
         void (*process_vertex_early)(const Vertex* v) = nullptr,
         void (*process_edge)(const Vertex* v1, const Vertex* v2,
                              double weight) = nullptr,
         void (*process_vertex_late)(const Vertex* v) = nullptr);

// DFS that traverses entire Graph (no specified search root).
void dfs_graph(Graph* graph,
               void (*process_vertex_early)(const Vertex* v) = nullptr,
               void (*process_edge)(const Vertex* v1, const Vertex* v2,
                                    double weight) = nullptr,
               void (*process_vertex_late)(const Vertex* v) = nullptr);

bool is_cyclic(Graph* graph);

// Repeatedly pop the stack returned by this function to obtain topological
// sort of a DAG.
std::stack<const Vertex*> topological_sort(Graph* graph);

// Forward declarations for functions common to BFS.
void print_vertex(const Vertex* v);
void print_edge(const Vertex* v1, const Vertex* v2, double weight);

}  // namespace graphlib
