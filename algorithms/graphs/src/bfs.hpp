#pragma once

#include "graph.hpp"

#include <map>
#include <set>
#include <stack>
#include <vector>

namespace graphlib {

// Traditional BFS algorithm.
std::map<Vertex, Vertex> bfs(
    Graph* graph, Vertex search_root,
    void (*process_vertex_early)(const Vertex* v) = nullptr,
    void (*process_edge)(const Vertex* v1, const Vertex* v2,
                         double weight) = nullptr,
    void (*process_vertex_late)(const Vertex* v) = nullptr);

// To obtain the shortest path, repeatedly pop the stack returned by this
// function.
std::stack<Vertex> shortest_path(Graph* graph, Vertex search_root,
                                 Vertex destination);

std::vector<std::set<Vertex>> connected_components(Graph* graph);

// Misc common vertex and edge processing functions
void print_vertex(const Vertex* v);
void print_edge(const Vertex* v1, const Vertex* v2, double weight);

}  // namespace graphlib
