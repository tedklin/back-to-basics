#pragma once

#include "bfs.hpp"
#include "graph.hpp"

namespace graphlib {

// Traditional DFS algorithm.
void dfs(Graph* graph, const Vertex* search_root,
         void (*process_vertex_early)(const Vertex* v) = nullptr,
         void (*process_edge)(const Vertex* v1, const Vertex* v2,
                              double weight) = nullptr,
         void (*process_vertex_late)(const Vertex* v) = nullptr);

bool is_cyclic(Graph* graph);

// Forward declarations for functions common to BFS.
std::stack<const Vertex*> find_path(Graph* graph, const Vertex* search_root,
                                    const Vertex* destination);
void print_vertex(const Vertex* v);
void print_edge(const Vertex* v1, const Vertex* v2, double weight);

}  // namespace graphlib
