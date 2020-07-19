#pragma once

#include "graph.hpp"

#include <vector>

namespace graphlib {

// Prim's algorithm. Assumes given graph is connected.
std::vector<Edge> prim_mst(Graph* graph);

// Kruskal's algorithm.
std::vector<Edge> kruskal_mst(Graph* graph);

}  // namespace graphlib
