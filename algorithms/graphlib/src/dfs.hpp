#pragma once

#include "bfs.hpp"
#include "graph.hpp"

namespace graphlib {

enum class EdgeType { TREE, BACK, FORWARD, CROSS, UNCLASSIFIED };

// Traditional DFS algorithm.
void dfs(Graph* graph, const Vertex* search_root,
         void (*process_vertex_early)(const Vertex* v) = nullptr,
         void (*process_edge)(const Vertex* v1, const Vertex* v2,
                              double weight) = nullptr,
         void (*process_vertex_late)(const Vertex* v) = nullptr);

bool is_cyclic(Graph* graph);

// Forward declarations for functions common to BFS.
void print_vertex(const Vertex* v);
void print_edge(const Vertex* v1, const Vertex* v2, double weight);

}  // namespace graphlib
