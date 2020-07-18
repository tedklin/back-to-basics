// The current DFS implementation (see dfs.cpp) is recursive with several global
// variables storing the information of interest. That is why most of the
// functions here are allowed to return by reference.

#pragma once

#include "bfs.hpp"
#include "graph.hpp"

#include <set>
#include <stack>

namespace graphlib {

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
std::stack<const Vertex*>& topological_sort(Graph* graph);

// TODO: test
std::set<const Vertex*>& articulation_vertices(Graph* graph);

// TODO: test
bool is_biconnected(Graph* graph);

// TODO: test
std::vector<std::set<const Vertex*>>& strong_components(Graph* graph);

// Forward declarations for functions common to BFS.
void print_vertex(const Vertex* v);
void print_edge(const Vertex* v1, const Vertex* v2, double weight);

}  // namespace graphlib
