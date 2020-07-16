#pragma once

#include "graph.hpp"

#include <map>

namespace graphlib {

// Traditional DFS algorithm.
void dfs(Graph* graph, const Vertex* search_root,
         void (*process_vertex_early)(const Vertex* v) = nullptr,
         void (*process_edge)(const Vertex* v1, const Vertex* v2,
                              double weight) = nullptr,
         void (*process_vertex_late)(const Vertex* v) = nullptr);

// Forward declarations for common vertex and edge processing functions.
// (common to BFS, defined in bfs.cpp)
void print_vertex(const Vertex* v);
void print_edge(const Vertex* v1, const Vertex* v2, double weight);

}  // namespace graphlib
