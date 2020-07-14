#pragma once

#include "graph.hpp"

// Traditional BFS algorithm.
std::map<const Vertex*, const Vertex*> bfs(
    Graph* graph, Vertex root, void (*process_vertex_early)(const Vertex* v),
    void (*process_edge)(const Vertex* v1, const Vertex* v2, double weight),
    void (*process_vertex_late)(const Vertex* v));

// Common vertex and edge processing functions
void print_vertex(const Vertex* v);
void print_edge(const Vertex* v1, const Vertex* v2, double weight);
